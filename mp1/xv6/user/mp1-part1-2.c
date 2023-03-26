#include "kernel/types.h"
#include "user/user.h"
#include "user/threads.h"

#define NULL 0

// In case the thread’s function just returns, the thread needs to be removed from the
// runqueue and the next one has to be dispatched. The easiest way to do this is to
// call thread_exit().
void f1(void *arg)
{
    return;
}

// Try to produce many orphans.
int main(int argc, char **argv)
{
    printf("mp1-part1-2\n");
    struct thread *t1 = thread_create(f1, NULL);
    thread_add_runqueue(t1);
    thread_start_threading();
    printf("\nexited\n");
    exit(0);
}
