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
    __attribute__((unused)) int num_threads = 3;

    struct thread *t1 = thread_create(f, NULL, 4, 13, 10);
    thread_add_at(t1, 2);

    struct thread *t2 = thread_create(f, NULL, 2, 10, 1);
    thread_add_at(t2, 9);

    struct thread *t3 = thread_create(f, NULL, 2, 9, 2);
    thread_add_at(t3, 2);

    thread_start_threading();
    printf("\nexited\n");
    exit(0);
}