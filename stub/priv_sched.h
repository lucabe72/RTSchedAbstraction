// Definitions taken from kernel/sched/sched.h


#define BW_SHIFT                20
#define BW_UNIT                 (1 << BW_SHIFT)
#define RATIO_SHIFT             8
#define MAX_BW_BITS             (64 - BW_SHIFT)
#define MAX_BW                  ((1ULL << MAX_BW_BITS) - 1)


//FIXME: real per-cpu thing!
struct rq runqueues[NR_CPUS];
//#define cpu_rq(cpu)             (&per_cpu(runqueues, (cpu)))
#define cpu_rq(cpu)             (&runqueues[cpu])
#define this_rq()               this_cpu_ptr(&runqueues)
#define task_rq(p)              cpu_rq(task_cpu(p))
#define cpu_curr(cpu)           (cpu_rq(cpu)->curr)
#define raw_rq()                raw_cpu_ptr(&runqueues)


/* task_struct::on_rq states: */
#define TASK_ON_RQ_QUEUED       1
#define TASK_ON_RQ_MIGRATING    2

static inline unsigned int task_cpu(const struct task_struct *p)
{
        return p->thread_info.cpu;
}

static inline void
queue_balance_callback(struct rq *rq,
                       struct balance_callback *head,
                       void (*func)(struct rq *rq))
{
// FIXME!!!! Implement something...
#if 0
	lockdep_assert_rq_held(rq);

        /*
         * Don't (re)queue an already queued item; nor queue anything when
         * balance_push() is active, see the comment with
         * balance_push_callback.
         */
        if (unlikely(head->next || rq->balance_callback == &balance_push_callback))
                return;

        head->func = func;
        head->next = rq->balance_callback;
        rq->balance_callback = head;
#endif
}


static inline int get_rd_overloaded(struct root_domain *rd)
{
        return rd->overloaded;
}

static inline void set_rd_overloaded(struct root_domain *rd, int status)
{
        if (get_rd_overloaded(rd) != status)
                rd->overloaded, status;
}

static inline void sched_update_tick_dependency(struct rq *rq) { } //We assume to disable NO_FULL_HZ

static inline void add_nr_running(struct rq *rq, unsigned count)
{
        unsigned prev_nr = rq->nr_running;

        rq->nr_running = prev_nr + count;
//        if (trace_sched_update_nr_running_tp_enabled()) {
//                call_trace_sched_update_nr_running(rq, count);
//        }

        if (prev_nr < 2 && rq->nr_running >= 2)
                set_rd_overloaded(rq->rd, 1);

        sched_update_tick_dependency(rq);
}

static inline void sub_nr_running(struct rq *rq, unsigned count)
{
        rq->nr_running -= count;
//        if (trace_sched_update_nr_running_tp_enabled()) {
//                call_trace_sched_update_nr_running(rq, -count);
//        }

        /* Check if we still need preemption */
        sched_update_tick_dependency(rq);
}

/*
 * Is p the current execution context?
 */
static inline int task_current(struct rq *rq, struct task_struct *p)
{
        return rq->curr == p;
}

static inline int task_on_rq_queued(struct task_struct *p)
{
        return p->on_rq == TASK_ON_RQ_QUEUED;
}

static inline bool sched_stop_runnable(struct rq *rq)
{
	return 0;
        //return rq->stop && task_on_rq_queued(rq->stop); FIXME?
}

static inline bool sched_dl_runnable(struct rq *rq)
{
        return false;	//FIXME?
}

static inline bool sched_rt_runnable(struct rq *rq)
{
        return rq->rt.rt_queued > 0;
}

static inline int task_on_cpu(struct rq *rq, struct task_struct *p)
{
        return p->on_cpu;
}
static inline bool task_is_pushable(struct rq *rq, struct task_struct *p, int cpu)
{
        if (!task_on_cpu(rq, p) &&
            cpumask_test_cpu(cpu, &p->cpus_mask))
                return true;
        
        return false;
}      

static inline bool is_migration_disabled(struct task_struct *p)
{
        return p->migration_disabled;
}

static inline int cpu_of(struct rq *rq)
{
        return rq->cpu;
}


/*
 * Is p the current scheduling context?
 *
 * Note that it might be the current execution context at the same time if
 * rq->curr == rq->donor == p.
 */
static inline int task_current_donor(struct rq *rq, struct task_struct *p)
{
        return rq->donor == p;
}

static inline struct task_struct *get_push_task(struct rq *rq)
{                                       
        struct task_struct *p = rq->donor;
        
        if (rq->push_busy)
                return NULL;

        if (p->nr_cpus_allowed == 1)
                return NULL;

        if (p->migration_disabled)
                return NULL;

        rq->push_busy = true;
        return get_task_struct(p);
}

/* This does really nothing, because we disabled hierarchical scheduling stuff */
static inline void set_task_rq(struct task_struct *p, unsigned int cpu)
{                            
}
static inline void set_task_cpu(struct task_struct *p, unsigned int cpu)
{       
        set_task_rq(p, cpu);
        /*
         * After ->cpu is set up to a new value, task_rq_lock(p, ...) can be
         * successfully executed on another CPU. We must ensure that updates of
         * per-task data have been completed by this moment.
         */ 
        //smp_wmb();
        p->thread_info.cpu = cpu;
        p->wake_cpu = cpu;
}


void move_queued_task_locked(struct rq *src_rq, struct rq *dst_rq, struct task_struct *task)
{
        deactivate_task(src_rq, task, 0);
        set_task_cpu(task, dst_rq->cpu);
        activate_task(dst_rq, task, 0);
}

#define DEFINE_SCHED_CLASS(name) \
const struct sched_class name##_sched_class

extern const struct sched_class rt_sched_class;


static inline void rq_unpin_lock(struct rq *rq, struct rq_flags *rf) {}
static inline void rq_repin_lock(struct rq *rq, struct rq_flags *rf) {}
static inline void raw_spin_rq_lock(struct rq *rq) {}
static inline void raw_spin_rq_unlock(struct rq *rq) {}

#define DEQUEUE_SLEEP           0x01 /* Matches ENQUEUE_WAKEUP */
#define DEQUEUE_SAVE            0x02 /* Matches ENQUEUE_RESTORE */
#define DEQUEUE_MOVE            0x04 /* Matches ENQUEUE_MOVE */
#define DEQUEUE_NOCLOCK         0x08 /* Matches ENQUEUE_NOCLOCK */
#define DEQUEUE_SPECIAL         0x10
#define DEQUEUE_MIGRATING       0x100 /* Matches ENQUEUE_MIGRATING */
#define DEQUEUE_DELAYED         0x200 /* Matches ENQUEUE_DELAYED */

#define ENQUEUE_WAKEUP          0x01
#define ENQUEUE_RESTORE         0x02
#define ENQUEUE_MOVE            0x04
#define ENQUEUE_NOCLOCK         0x08

#define ENQUEUE_HEAD            0x10
#define ENQUEUE_REPLENISH       0x20
#define ENQUEUE_MIGRATED        0x40
#define ENQUEUE_INITIAL         0x80
#define ENQUEUE_MIGRATING       0x100
#define ENQUEUE_DELAYED         0x200
#define ENQUEUE_RQ_SELECTED     0x400


/* Wake flags. The first three directly map to some SD flag value */
#define WF_EXEC                 0x02 /* Wakeup after exec; maps to SD_BALANCE_EXEC */
#define WF_FORK                 0x04 /* Wakeup after fork; maps to SD_BALANCE_FORK */
#define WF_TTWU                 0x08 /* Wakeup;            maps to SD_BALANCE_WAKE */

#define WF_SYNC                 0x10 /* Waker goes to sleep after wakeup */
#define WF_MIGRATED             0x20 /* Internal use, task got migrated */
#define WF_CURRENT_CPU          0x40 /* Prefer to move the wakee to the current CPU. */
#define WF_RQ_SELECTED          0x80 /* ->select_task_rq() was called */

