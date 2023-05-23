#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

#define min(a,b) \
    ({ \
        __typeof__ (a) _a = (a); \
        __typeof__ (b) _b = (b); \
        _a < _b ? _a : _b; \
    })

// search available context block with linear search
static int
available_ctx(const int *arr, int size)
{
  const int *end = arr + size;
  const int *ptr = arr;

  while (ptr != end) {
    if (!(*ptr)) {
      return ptr - arr;
    }

    ptr++;
  }

  return 0;
}

// for mp3
uint64
sys_thrdstop(void)
{
  int delay;
  uint64 context_id_ptr;
  uint64 handler, handler_arg;
  if (argint(0, &delay) < 0)
    return -1;
  if (argaddr(1, &context_id_ptr) < 0)
    return -1;
  if (argaddr(2, &handler) < 0)
    return -1;
  if (argaddr(3, &handler_arg) < 0)
    return -1;

  struct proc *proc = myproc();
  int context_id;

  // copy id from user space, check if process needs to allocate a
  // block for current context.
  copyin(proc->pagetable, (char *)&context_id, context_id_ptr, sizeof(int));

  // search for free block, otherwise return failure to user.
  if (context_id == -1) {
    context_id = available_ctx(proc->thrdstop_used, MAX_THRD_NUM);

    // syscall() sets 'a0' as retval.
    if (context_id == -1) {
      return -1;
    }

    // set context id to user if found an empty block.
    copyout(proc->pagetable, context_id_ptr, (char *)&context_id, sizeof(int));
  }

  // validate if id is valid
  if (context_id < 0 || context_id >= MAX_THRD_NUM) {
    return -1;
  }

  // store trapframe such that user can restore the context via thrdresume().
  proc->thrdstop_used[context_id] = 1;
  proc->thrdstop_trapframe = &proc->thrdstop_ctx[context_id];

  proc->handler = handler;
  proc->handler_arg = handler_arg;
  proc->handler_state = SLEEPING;

  // marks ticks
  proc->start_ticks = ticks;
  proc->deadline_ticks = ticks + delay;

  return 0;
}

// for mp3
uint64
sys_cancelthrdstop(void)
{
  int context_id, is_exit;
  if (argint(0, &context_id) < 0)
    return -1;
  if (argint(1, &is_exit) < 0)
    return -1;

  if (context_id < 0 || context_id >= MAX_THRD_NUM) {
    return -1;
  }

  struct proc *proc = myproc();
  struct trapframe *ctx = &proc->thrdstop_ctx[context_id];
  int ret = 0;

  if (is_exit) {
    // if is_exit is 1
    // do not store the current context, instead, release the stored context specified
    // by context_id and recycle this ID for other uses.
    proc->thrdstop_used[context_id] = 0;
    proc->handler_state = UNUSED;
  } else {
    // if is_exit is 0
    // it store the current context according to the context id.
    memmove(ctx, proc->trapframe, sizeof(struct trapframe));
  }

  // The return value is the number of ticks consumed by the process since thrdstop is called.
  // If the timer is inactive now (i.e. the handler has been executed), return the number of
  // ticks consumed by the previous timer.

  // mark ticks (potential overflow issue)
  proc->deadline_ticks = min(ticks, proc->deadline_ticks);
  ret = proc->deadline_ticks - proc->start_ticks;
  return ret;
}

// for mp3
uint64
sys_thrdresume(void)
{
  int context_id;
  if (argint(0, &context_id) < 0)
    return -1;

  struct proc *proc = myproc();
  struct trapframe *ctx = &proc->thrdstop_ctx[context_id];

  // out-of-range
  if (context_id < 0 || context_id >= MAX_THRD_NUM)
    return -1;

  // not registered
  if (!proc->thrdstop_used[context_id])
    return -1;

  // restore context to trapframe
  memmove(proc->trapframe, ctx, sizeof(struct trapframe));

  return 0;
}
