#include "kernel/types.h"
#include "user/user.h"
#include "user/threads.h"

int main_id = -1;
int is_handler_executed = 0;

void handler(void *arg)
{
    is_handler_executed = 1;
    thrdresume(main_id);
}

int main()
{
    thrdstop(10, &main_id, handler, (void *)0);
    while (!is_handler_executed) {
        /* wait for handler */
    }

    int t = cancelthrdstop(main_id, 0);
    printf("%d\n", t);

    thrdstop(10000, &main_id, handler, (void *)0);
    int start_time = uptime();

    while (uptime() - start_time < 3) {
        /* wait for 3 ticks */
    }
    t = cancelthrdstop(main_id, 0);
    printf("%d\n", t);

    exit(0);
}