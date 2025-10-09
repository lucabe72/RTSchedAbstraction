#include <string.h>

unsigned int _this_cpu;
static inline unsigned int smp_processor_id(void)
{
  return _this_cpu;
}

#include "compiler_attributes.h"

#define atomic_read(x) *(x) 
#define atomic_read_acquire(x) *(x) 
#define smp_rmb()
#define smp_wmb()
#define READ_ONCE(a) (a)
#define rcu_read_lock()
#define rcu_read_unlock()
//All scheduling features disabled... FIXME: should we improve this?
#define sched_feat(x) 0
//No NUMA
#define cpu_to_node(cpu) 0


#define DEFINE_PER_CPU(type, name) type name[NR_CPUS]
#define per_cpu(v, n) v[n]
#define this_cpu_cpumask_var_ptr(x) x[_this_cpu]
#define this_cpu_ptr(x) x[_this_cpu]

#define preempt_disable()
#define preempt_enable()

#define GFP_KERNEL 1

#include "typedefs.h"
#include "struct_defs.h"

#include "list.h"
#include "plist.h"


#define NR_CPUS 16
#define HZ 1000

unsigned int nr_cpu_ids = NR_CPUS;

static inline void atomic_inc(atomic_t *v)
{
  *v = *v + 1;
}

static inline void atomic_dec(atomic_t *v)
{
  *v = *v - 1;
}

static inline void atomic_set_release(atomic_t *v, int i)
{
  *v = i;
}

static inline int atomic_cmpxchg_acquire(atomic_t *v, int old, int new)
{
  int res = *v;

  if (*v == old) {
    *v = new;
  }

  return res;
}

static inline struct task_struct *get_task_struct(struct task_struct *t)
{
        //refcount_inc(&t->usage);
        return t;
}

static inline void put_task_struct(struct task_struct *t)
{
        //refcount_dec(&t->usage);
}

#define bitmap_size(nbits)      (nbits / (sizeof(long) * 8) / 8)
static inline void bitmap_zero(unsigned long *dst, unsigned int nbits)
{
        unsigned int len = bitmap_size(nbits); 

        memset(dst, 0, len);
}

static inline void bitmap_copy(unsigned long *dst, const unsigned long *src, unsigned int nbits)
{
        unsigned int len = bitmap_size(nbits);

        memcpy(dst, src, len);
}

unsigned long find_next_bit(const unsigned long *addr, unsigned long nbits, unsigned long start)
{
  unsigned int i;
  for (i = start; i < sizeof(long) * 8; i++) {
    if (*addr & 1ul << i) {
      return i;
    }

  }
  return nbits + 1;
}

#define for_each_set_bit(bit, addr, size) \
        for ((bit) = 0; (bit) = find_next_bit((addr), (size), (bit)), (bit) < (size); (bit)++)




// From include/uapi/linux/sched.h
/*
 * Scheduling policies
 */
#define SCHED_NORMAL            0
#define SCHED_FIFO              1
#define SCHED_RR                2
#define SCHED_BATCH             3
/* SCHED_ISO: reserved but not implemented yet */
#define SCHED_IDLE              5
#define SCHED_DEADLINE          6
#define SCHED_EXT               7


#include "thread_info.h"

#include "kassert.h"
#include "types.h"
#include "pid_types.h"
#include "sched_entity.h"
#include "sched_rt_entity.h"
#include "sched_dl_entity.h"

#include "bitops.h"
#include "container_of.h"

#include "cpumask.h"
#include "task.h"
#include "prio.h"
#include "dl.h"
#include "rt.h"
#include "root_domain.h"
#include "rt_prio_array.h"
#include "rt_rq.h"
#include "rq.h"
#include "sched_class.h"
#include "rq_clock.h"

typedef int (*cpu_stop_fn_t)(void *arg);
static inline bool stop_one_cpu_nowait(unsigned int cpu, cpu_stop_fn_t fn, void *arg, struct cpu_stop_work *work_buf) {}
static int push_cpu_stop(void *arg) {}
static void activate_task(struct rq *rq, struct task_struct *p, int flags) {}
static void deactivate_task(struct rq *rq, struct task_struct *p, int flags) {}

#include "priv_sched.h"

#include "spinlock.h"

static inline int test_tsk_need_resched(struct task_struct *tsk)
{
  return 0;
}
static inline void resched_curr(struct rq *rq) {};
s64 update_curr_common(struct rq *rq) {return 0;};
static inline void cpufreq_update_util(struct rq *rq, unsigned int flags) { }

/* Used in tsk->__state: */
#define TASK_RUNNING                    0x00000000
#define TASK_INTERRUPTIBLE              0x00000001
#define TASK_UNINTERRUPTIBLE            0x00000002
#define __TASK_STOPPED                  0x00000004
#define __TASK_TRACED                   0x00000008
/* Used in tsk->exit_state: */
#define EXIT_DEAD                       0x00000010
#define EXIT_ZOMBIE                     0x00000020
#define EXIT_TRACE                      (EXIT_ZOMBIE | EXIT_DEAD)
/* Used in tsk->__state again: */
#define TASK_PARKED                     0x00000040
#define TASK_DEAD                       0x00000080
#define TASK_WAKEKILL                   0x00000100
#define TASK_WAKING                     0x00000200
#define TASK_NOLOAD                     0x00000400
#define TASK_NEW                        0x00000800
#define TASK_RTLOCK_WAIT                0x00001000 
#define TASK_FREEZABLE                  0x00002000
#define __TASK_FREEZABLE_UNSAFE        (0x00004000 * IS_ENABLED(CONFIG_LOCKDEP))
#define TASK_FROZEN                     0x00008000
#define TASK_STATE_MAX                  0x00010000

#define TASK_ANY                        (TASK_STATE_MAX-1)


#define CPUPRI_NR_PRIORITIES    (MAX_RT_PRIO+1)

#define CPUPRI_INVALID          -1
#define CPUPRI_NORMAL            0
/* values 1-99 are for RT1-RT99 priorities */
#define CPUPRI_HIGHER           100
static inline int cpupri_find(struct cpupri *cp, struct task_struct *p, struct cpumask *lowest_mask) {return 0;}
static inline int cpupri_find_fitness(struct cpupri *cp, struct task_struct *p,
                         struct cpumask *lowest_mask,
                         bool (*fitness_fn)(struct task_struct *p, int cpu)) {return 0;}
static inline void cpupri_set(struct cpupri *cp, int cpu, int pri) {}
static inline int cpupri_init(struct cpupri *cp) {return 0;}
static inline void cpupri_cleanup(struct cpupri *cp) {}

static inline int update_rt_rq_load_avg(u64 now, struct rq *rq, int running)
{
        return 0;
}

static __always_inline bool sched_asym_cpucap_active(void)
{
        return false;
}

# define   schedstat_enabled()          0
# define __schedstat_inc(var)           do { } while (0)
# define   schedstat_inc(var)           do { } while (0)
# define __schedstat_add(var, amt)      do { } while (0)
# define   schedstat_add(var, amt)      do { } while (0)
# define __schedstat_set(var, val)      do { } while (0)
# define   schedstat_set(var, val)      do { } while (0)
# define   schedstat_val(var)           0
# define   schedstat_val_or_zero(var)   0

# define __update_stats_wait_start(rq, p, stats)       do { } while (0)
# define __update_stats_wait_end(rq, p, stats)         do { } while (0)
# define __update_stats_enqueue_sleeper(rq, p, stats)  do { } while (0)
# define check_schedstat_required()                    do { } while (0)


#include "sched_domain.h"

#define for_each_domain(cpu, __sd) \
        for (__sd = cpu_rq(cpu)->sd; \
                        __sd; __sd = __sd->parent)

static inline struct cpumask *sched_domain_span(struct sched_domain *sd)
{
        return to_cpumask(sd->span);
}

#define SD_WAKE_AFFINE 1

void sched_get_rd(struct root_domain *rd)
{
        atomic_inc(&rd->refcount);
}

void sched_put_rd(struct root_domain *rd)
{
//        if (!atomic_dec_and_test(&rd->refcount))
//                return;
//
//        call_rcu(&rd->rcu, free_rootdomain);
	atomic_dec(&rd->refcount);
}


static bool irq_work_queue_on(struct irq_work *work, int cpu) {return false;}
static void set_cpus_allowed_common(struct task_struct *p, struct affinity_context *ctx) {}
#define print_rt_rq(m, cpu, rt_rq)

#include "rt.c"
