#include "param.h"
#include "types.h"
#include "memlayout.h"
#include "riscv.h"
#include "spinlock.h"
#include "defs.h"
#include "proc.h"

/* NTU OS 2022 */
/* Page fault handler */
int handle_pgfault() {
  /* Find the address that caused the fault */

  // In handle_pgfault(), call uint64 va = r_stval() to find the offending virtual address,
  // and round the address to page boundary using PGROUNDDOWN().
  pagetable_t pagetable = myproc()->pagetable;
  uint64 pa, va = r_stval();
  uint64 a = PGROUNDDOWN(va);
  uint blk;

  // probably the page is valid but swapped out.
  pte_t *pte = walk(pagetable, a, 1);
  if (*pte & PTE_S) {
    begin_op();

    pa = (uint64)kalloc(); blk = PTE2BLOCKNO(*pte);
    read_page_from_disk(ROOTDEV, (char *)pa, blk);
    bfree_page(ROOTDEV, blk);

    end_op();

    *pte = PA2PTE(pa) | ((PTE_FLAGS(*pte) & ~PTE_S) | PTE_V);
    return 0;
  }

  // Demand paging
  // Always mark PTE_U, PTE_R, PTE_W, PTE_X flags on newly allocated pages.
  pa = (uint64)kalloc();
  int ret = mappages(pagetable, a, PGSIZE, pa, PTE_R | PTE_W | PTE_X | PTE_U);
  if (ret) {
    kfree((void *)pa);
    return -1;
  }

  memset((void *)pa, 0, PGSIZE);

  // printf("handle_pgfault: %p\n", va);
  // vmprint(pagetable);

  return 0;
}
