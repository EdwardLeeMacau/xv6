#include "kernel/types.h"
#include "threads.h"
#include "threads_sched.h"
#include "user/user.h"
#include "user/list.h"
#include "user/threads.h"
#include "user/threads_sched.h"

#define NULL 0

#define max(a,b) \
    ({ \
        __typeof__ (a) _a = (a); \
        __typeof__ (b) _b = (b); \
        _a > _b ? _a : _b; \
    })

#define min(a,b) \
    ({ \
        __typeof__ (a) _a = (a); \
        __typeof__ (b) _b = (b); \
        _a < _b ? _a : _b; \
    })

static int next_release_time(struct threads_sched_args args)
{
    struct release_queue_entry *entry = NULL;
    int x = 0x7fffffff; // INT_MAX

    list_for_each_entry(entry, args.release_queue, thread_list) {
        x = min(x, entry->release_time);
    }

    return x;
}

/* default scheduling algorithm */
struct threads_sched_result schedule_default(struct threads_sched_args args)
{
    struct thread *thread_with_smallest_id = NULL;
    struct thread *th = NULL;
    list_for_each_entry(th, args.run_queue, thread_list) {
        if (thread_with_smallest_id == NULL || th->ID < thread_with_smallest_id->ID) {
            thread_with_smallest_id = th;
        }
    }

    struct threads_sched_result r;
    if (thread_with_smallest_id != NULL) {
        r.scheduled_thread_list_member = &thread_with_smallest_id->thread_list;
        r.allocated_time = thread_with_smallest_id->remaining_time;
    } else {
        r.scheduled_thread_list_member = args.run_queue;
        r.allocated_time = 1;
    }

    return r;
}

/* Earliest-Deadline-First scheduling */
struct threads_sched_result schedule_edf(struct threads_sched_args args)
{
    struct threads_sched_result r;

    struct release_queue_entry *entry;
    struct thread *target_thread = NULL;
    struct thread *th = NULL;
    int x;

    // Select the thread with earliest deadline from run-queue
    list_for_each_entry(th, args.run_queue, thread_list) {
        if (!target_thread
           || ((x = th->current_deadline - target_thread->current_deadline) < 0)
           || (x == 0 && th->ID < target_thread->ID)) {
            target_thread = th;
        }
    }

    if (target_thread != NULL) {
        // Find nearest next deadline.
        x = target_thread->current_deadline;
        list_for_each_entry(entry, args.release_queue, thread_list) {
            // Check if the task would be preempted by to-be-released task
            // available ticks decrease to its release time
            th = entry->thrd;
            if (entry->release_time + th->period < x)
                x = entry->release_time;
        }

        r.scheduled_thread_list_member = &target_thread->thread_list;
        r.allocated_time = min(x - args.current_time, target_thread->remaining_time);
    } else {
        r.scheduled_thread_list_member = args.run_queue;
        r.allocated_time = next_release_time(args) - args.current_time;
    }

    return r;
}

/* Rate-Monotonic Scheduling */
struct threads_sched_result schedule_rm(struct threads_sched_args args)
{
    struct threads_sched_result r;

    struct release_queue_entry *entry;
    struct thread *target_thread = NULL;
    struct thread *th = NULL;
    int x;

    // Check if any thread is expired
    list_for_each_entry(th, args.run_queue, thread_list) {
        if (th->current_deadline > args.current_time)
            continue;

        if (!target_thread) {
            target_thread = th; continue;
        }

        if (th->ID < target_thread->ID) {
            target_thread = th; continue;
        }
    }

    if (target_thread) {
        r.scheduled_thread_list_member = &target_thread->thread_list;
        r.allocated_time = 0;

        return r;
    }

    // Select the thread with shortest period from run-queue
    list_for_each_entry(th, args.run_queue, thread_list) {
        if (!target_thread
           || ((x = th->period - target_thread->period) < 0)
           || (x == 0 && th->ID < target_thread->ID)) {
            target_thread = th;
        }
    }

    if (target_thread != NULL) {
        // printf(
        //     "[%d] thread#%d, current_deadline: %d, remaining_time: %d\n",
        //     args.current_time, target_thread->ID, target_thread->current_deadline, target_thread->remaining_time);

        // Find nearest next deadline.
        x = target_thread->current_deadline;

        list_for_each_entry(entry, args.release_queue, thread_list) {
            // Check if the task would be preempted by to-be-released task
            // available ticks decrease to its release time
            th = entry->thrd;
            if (th->period < target_thread->period)
                x = min(x, entry->release_time);
        }

        r.scheduled_thread_list_member = &target_thread->thread_list;
        r.allocated_time = min(x - args.current_time, target_thread->remaining_time);
        r.allocated_time = max(r.allocated_time, 0);
    } else {
        r.scheduled_thread_list_member = args.run_queue;
        r.allocated_time = next_release_time(args) - args.current_time;
    }

    return r;
}
