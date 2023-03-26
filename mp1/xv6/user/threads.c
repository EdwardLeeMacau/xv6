#include "kernel/types.h"
#include "user/setjmp.h"
#include "user/threads.h"
#include "user/user.h"

#define NULL 0
#define link_element(_p, _n) \
    do { \
        struct thread *prev = _p, *next = _n; \
        prev->next = next; next->previous = prev; \
    } while (0)


// Note:
// thread_register_handler() and thread_kill() won’t be called in the main thread.
static struct thread* current_thread = NULL;
static int id = 1;
static jmp_buf env_st;
// __attribute__((unused)) static jmp_buf env_tmp;

// __attribute__((unused)) static void
// handler_default(int signo)
// {
//     thread_exit();
// }

// Function Description:
//
// This function creates a new thread and allocates the space in stack to the thread.
//
// Note, if you would like to allocate a new stack for the thread, it is important that
// the address of the stack pointer should be divisible by 8. The function returns the
// initialized structure. If you want to use your own template for creating thread, make
// sure it works for the provided test cases.
//
// @param[in] f      thread routine
// @param[in] arg    argument for routine
struct thread *
thread_create(void (*f)(void *), void *arg)
{
    struct thread *t = (struct thread*) malloc(sizeof(struct thread));
    unsigned long new_stack_p;
    unsigned long new_stack;
    new_stack = (unsigned long) malloc(sizeof(unsigned long)*0x100);
    new_stack_p = new_stack +0x100*8-0x2*8;
    t->fp = f;
    t->arg = arg;
    t->ID  = id;
    t->buf_set = 0;
    t->stack = (void*) new_stack;
    t->stack_p = (void*) new_stack_p;
    id++;

    // part 2
    t->sig_handler[0] = NULL_FUNC;
    t->sig_handler[1] = NULL_FUNC;
    t->signo = -1;
    t->handler_buf_set = 0;
    return t;
}

// Function Description:
//
// This function adds an initialized struct thread to the runqueue.
//
// To implement the scheduling functionality, you’ll need to maintain a circular linked list
// of struct thread. You should implement that by maintaining the next and previous field in
// struct thread which always points to the next to-be-executed thread and the previously
// executed thread respectively.
//
// You should also maintain the static variable struct thread *current thread that always
// points to the currently executed thread. Note: Please insert the new thread at the end
// of the runqueue, i.e. the newly inserted thread should be current thread->previous.
//
// you should let the child thread `t` inherit the signal handlers from current thread.
void
thread_add_runqueue(struct thread *t)
{
    if (current_thread == NULL) {
        current_thread = t;
        t->next = t->previous = t;
    } else {
        struct thread *tail = current_thread->previous;

        link_element(tail, t);
        link_element(t, current_thread);

        // Inherit signal handler.
        t->sig_handler[0] = current_thread->sig_handler[0];
        t->sig_handler[1] = current_thread->sig_handler[1];
    }
}

// Function Description:
//
// This function suspends the current thread by saving its context to the jmp_buf in struct
// thread using setjmp.
//
// The setjmp in xv6 is provided to you, therefore you only need to add #include "user/setjmp.h"
// to your code. After saving the context, you should call schedule() to determine which thread
// to run next and then call dispatch() to execute the new thread. If the thread is resumed
// later, thread_yield() should return to the calling place in the function.
//
// If this function is called in the signal handler, you should save the context in another jmp_buf to
// prevent from discarding the context of the thread function.
void
thread_yield(void)
{
    jmp_buf *buf;
    int *flag;

    if (current_thread->signo == -1) {
        buf = &current_thread->env;
        flag = &current_thread->buf_set;
    } else {
        buf = &current_thread->handler_env;
        flag = &current_thread->handler_buf_set;
    }

    switch (setjmp(*buf)) {
    case 0: // jmp is set, switch to next task.
        // update stack pointer for reusing stack memory
        // when thread receives signal.
        current_thread->stack_p = (void *)((*buf)->sp);

        // switch to next task.
        *flag = 1;
        schedule();
        dispatch();
        break;

    case 1: // transfer control back
        *flag = 0;
        break;
    }

    return;
}

// Function Description:
//
// This function executes a thread which decided by schedule().
//
// In case the thread has never run before, you may need to do some initialization such as
// moving the stack pointer sp to the allocated stack of the thread. The stack pointer sp
// could be accessed and modified using setjmp and longjmp. Please take a look at setjmp.h
// to understand where the sp is stored in jmp_buf. If the thread was executed before,
// restoring the context with longjmp is enough.
//
// In case the thread’s function just returns, the thread needs to be removed from the
// runqueue and the next one has to be dispatched. The easiest way to do this is to call
// thread_exit().
//
// If a signal came, this function will call the corresponding signal handler. However,
// if such signal handler has not been registered, then current thread should be killed,
// i.e. calling thread_exit() directly. In case the handler has never run before, you may
// need to do some initialization.
//
// If the signal handler was executed before, restoring the context with longjmp is enough.
// In case the signal handler just returns, the thread should continue executing the original
// thread function from the place where it was interrupted by the signal. Surely, it is
// possible that a signal comes before the thread executes its thread function.
void
dispatch(void)
{
    // all routine are done, jump back to thread_start_threading().
    if (current_thread == NULL) {
        longjmp(env_st, 1);
    }

    // receive signal
    int signo = current_thread->signo;
    if (signo != -1) {
        // maybe a default handler is thread_exit()
        void (*handler)(int) = current_thread->sig_handler[signo];
        if (handler == NULL_FUNC) {
            thread_exit();
        } else {
            // Thread local signal handler stack initialization, similar to default routine.
            if (!current_thread->handler_buf_set) {
                if (setjmp(current_thread->handler_env) == 0) {
                    current_thread->handler_env->sp = (unsigned long)current_thread->stack_p;
                    current_thread->handler_buf_set = 1;
                    longjmp(current_thread->handler_env, 1);
                } else {
                    handler(signo);
                }
            } else {
                longjmp(current_thread->handler_env, 1);
            }

            signo = -1;
        }
    }

    if (!current_thread->buf_set) {
        // Thread local stack initialization:
        //
        // Utilize property of longjmp() to switch program stack.
        // Then, mark metadata 'buf_set' as 1 to indicate the initialization is done.
        if (setjmp(current_thread->env) == 0) {
            current_thread->env->sp = (unsigned long)current_thread->stack_p;
            current_thread->buf_set = 1;
            longjmp(current_thread->env, 1);
        } else {
            current_thread->fp(current_thread->arg);
        }
    } else {
        longjmp(current_thread->env, 1);
    }

    // Handle thread's function just returns, here is an implicit thread_exit().
    thread_exit();

    return;
}

// Function Description:
//
// This function will decide which thread to run next.
//
// It is actually trivial, since you will just run the next thread in the circular linked
// list of threads. You can simply change current thread to the next field of current thread.
void
schedule(void)
{
    if (current_thread == NULL) {
        return;
    }

    current_thread = current_thread->next;
    return;
}

// Function Description:
//
// This function removes the calling thread from the runqueue, frees its stack
// and the struct thread, updates current thread with the next to-be-executed thread in the runqueue
// and calls dispatch().
//
// Furthermore, think about what happens when the last thread exits (should return to the main function
// by some means).
void
thread_exit(void)
{
    struct thread *tmp = current_thread;

    if (current_thread->next != current_thread) {
        link_element(current_thread->previous, current_thread->next);
        current_thread = current_thread->next;
    } else {
        // Hint: No more thread to execute
        current_thread = NULL;
    }

    free(tmp->stack);
    free(tmp);

    dispatch();
}

// Function Description:
//
// This function will be called by the main function after the first thread is added to
// the runqueue.
//
// It should return only if all threads have exited
void
thread_start_threading(void)
{
    // store process stack to 'env_st'
    __attribute__((unused)) int jmp_val = setjmp(env_st);

    while (current_thread != NULL) {
        dispatch();
    }

    return;
}

// Function Description:
//
// This function receives two arguments:
// first argument as an integer which represents signal number and second argument as a pointer
// to the signal-handling function.
//
// This function sets handler to current thread for signal signo.
// If current thread has registered a signal handler corresponding to this signal, just replace it.
void
thread_register_handler(int signo, void (*handler)(int))
{
    current_thread->sig_handler[signo] = handler;
}

// Function Description:
//
// This function sends a signal signo to t.
//
// If t has a corresponding signal handler for the signal signo, it will be executed firstly
// when t is resumed later. Otherwise, t will be killed, that is, thread_exit() is called directly
// when t is resumed.
//
// Note that, (1) if a thread returns from its signal handler, it should continue executing the
// original thread function from the place where it was interrupted by the signal. (2) This
// function only sends a signal and does not trigger any context switch.
void
thread_kill(struct thread *t, int signo)
{
    t->signo = signo;
}
