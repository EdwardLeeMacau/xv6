#include "kernel/types.h"
#include "user/user.h"
#include "user/threads.h"

#define NULL 0

void f2(void *arg)
{
    int i = 0;

    while (1) {
        printf("thread 2: %d\n", i++);
        if (i == 2) {
            printf("thread 2: %d\n", *((int *)arg));
            thread_exit();
        }
        thread_yield();
    }

    return;
}

// In case the thread’s function just returns, the thread needs to be removed from the
// runqueue and the next one has to be dispatched. The easiest way to do this is to
// call thread_exit().
void f1(void *arg)
{
    int i = 0;

    printf("thread 1: %d\n", i);
    struct thread *t2 = thread_create(f2, &i);
    thread_add_runqueue(t2);
    thread_yield();

    printf("thread 1 exit\n");
    i = 0xDEADBEEF;
    thread_exit();

    return;
}

// Try to produce many orphans.
int main(int argc, char **argv)
{
    printf("mp1-part1-5\n");
    struct thread *t1 = thread_create(f1, NULL);
    thread_add_runqueue(t1);
    thread_start_threading();
    printf("\nexited\n");
    exit(0);
}
