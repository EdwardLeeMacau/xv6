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
    __attribute__((unused)) int num_threads = 7;

    struct thread *t1 = thread_create(f, NULL, 2, 12, 9);
    thread_add_at(t1, 0);

    struct thread *t2 = thread_create(f, NULL, 3, 13, 5);
    thread_add_at(t2, 4);

    struct thread *t3 = thread_create(f, NULL, 3, 15, 6);
    thread_add_at(t3, 5);

    struct thread *t4 = thread_create(f, NULL, 1, 9, 6);
    thread_add_at(t4, 7);

    struct thread *t5 = thread_create(f, NULL, 1, 12, 9);
    thread_add_at(t5, 4);

    struct thread *t6 = thread_create(f, NULL, 3, 13, 7);
    thread_add_at(t6, 7);

    struct thread *t7 = thread_create(f, NULL, 5, 13, 10);
    thread_add_at(t7, 7);

    thread_start_threading();
    printf("\nexited\n");
    exit(0);
}
