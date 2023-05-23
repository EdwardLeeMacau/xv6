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
    __attribute__((unused)) int num_threads = 5;

    struct thread *t1 = thread_create(f, NULL, 2, 10, 6);
    thread_add_at(t1, 5);

    struct thread *t2 = thread_create(f, NULL, 2, 11, 4);
    thread_add_at(t2, 0);

    struct thread *t3 = thread_create(f, NULL, 5, 13, 1);
    thread_add_at(t3, 7);

    struct thread *t4 = thread_create(f, NULL, 2, 12, 10);
    thread_add_at(t4, 4);

    struct thread *t5 = thread_create(f, NULL, 3, 11, 3);
    thread_add_at(t5, 0);

    thread_start_threading();
    printf("\nexited\n");
    exit(0);
}