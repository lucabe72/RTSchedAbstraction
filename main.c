#include <stdio.h>

#include "my_alloc.h"

#include "stub/compiler_attributes.h"

#define NR_CPUS 16			// FIXME!
#define ENQUEUE_WAKEUP          0x01	// FIXME!

#include "stub/bitops.h"
#include "stub/typedefs.h"
#include "stub/struct_defs.h"
#include "stub/types.h"
#include "stub/thread_info.h"
#include "stub/list.h"
#include "stub/plist.h"
#include "stub/sched_dl_entity.h"
#include "stub/sched_entity.h"
#include "stub/cpumask_types.h"
#include "prio.h"
#include "rt_prio_array.h"
#include "sched_rt_entity.h"
#include "pid_types.h"
#include "task.h"
#include "rt_rq.h"
#include "root_domain.h"
#include "rq.h"
#include "sched_class.h"

struct rq runqueues[NR_CPUS];

extern struct sched_class rt_sched_class;
void init_sched_rt_class(void);
void init_rt_rq(struct rt_rq *rt_rq);

struct cpumask __cpu_online_mask;
struct cpumask __cpu_possible_mask;

void add_task(struct rq *rq)
{
  struct task_struct *t;
  static unsigned int id = 1;

  t = my_alloc(sizeof(struct task_struct));
  t->pid = id++;
  t->prio = 20 - t->pid;
  printf("Adding %p %d (prio %d) to %p %d\n", t, t->pid, t->prio, rq, rq->cpu);
  rt_sched_class.enqueue_task(rq, t, ENQUEUE_WAKEUP);
}

struct root_domain *create_root_domain(unsigned int num_rqs)
{
  struct root_domain *rd;
  unsigned int i;

  rd = my_alloc(sizeof(struct root_domain));
  rd->refcount = num_rqs;
  for (i = 0; i < num_rqs; i++) {
    //cpumask_set_cpu(i, &rd->span);
    //cpumask_set_cpu(i, &rd->online);
    rd->span->bits[0] = 0xf;
    rd->online->bits[0] = 0xf;
  }
  rd->rto_cpu = -1;

  return rd;
}

void do_schedule(struct rq *rq)
{
  struct task_struct *exec;

  exec = rt_sched_class.pick_task(rq);
  if (exec) {
    printf("Task %d scheduled on CPU %d\n", exec->pid, rq->cpu);
  } else {
    printf("No task scheduled on CPU %d\n", rq->cpu);
  }
}

int main()
{
  unsigned int i;
  struct root_domain *rd;

  __cpu_online_mask.bits[0] = 0xf;
  __cpu_possible_mask.bits[0] = 0xf;
  init_sched_rt_class();
  rd = create_root_domain(4);

  for (i = 0; i < 4; i++) {
    struct rq *rq;

    rq = &runqueues[i]; //FIXME: should use cpu_rq(i)
    rq->cpu = i;
    init_rt_rq(&rq->rt);
    rq->rd = rd;
    //TODO: Initialize the rq structure, to avoid asserts and crashes!
  }

  add_task(&runqueues[0]);
  add_task(&runqueues[0]);
 
  do_schedule(&runqueues[0]);
  do_schedule(&runqueues[1]);
  do_schedule(&runqueues[2]);
  do_schedule(&runqueues[3]);

  return 0;
}
