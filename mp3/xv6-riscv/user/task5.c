#include "kernel/types.h"
#include "user/user.h"
#include "user/threads.h"

#define NULL 0

int k = 0;

void f(void *arg)
{
    while (1) {
        k++;
    }
}

int main(int argc, char **argv)
{
    struct thread *t1 = thread_create(f, NULL, 1, 4, 1);
    thread_add_at(t1, 0);

    struct thread *t2 = thread_create(f, NULL, 1, 5, 1);
    thread_add_at(t2, 0);

    struct thread *t3 = thread_create(f, NULL, 2, 8, 1);
    thread_add_at(t3, 0);

    struct thread *t4 = thread_create(f, NULL, 3, 12, 2);
    thread_add_at(t4, 50);

    thread_start_threading();
    printf("\nexited\n");
    exit(0);
}
