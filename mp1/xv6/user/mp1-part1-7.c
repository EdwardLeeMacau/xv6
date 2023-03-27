#include "kernel/types.h"
#include "user/user.h"
#include "user/threads.h"

#define NULL 0

void f3(void *arg)
{
    printf("thread 3\n");
    thread_exit();
}

void f2(void *arg)
{
    int i = 0;

    while (i < 18) {
        printf("thread 2: %d\n", i++);
        thread_add_runqueue(thread_create(f3, NULL));
    }

    thread_exit();
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

    struct thread *t3 = thread_create(f3, NULL);
    thread_add_runqueue(t3);
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
