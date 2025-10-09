#include <stdio.h>
#include <string.h>

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
#include "rq.h"
#include "sched_class.h"

extern struct sched_class rt_sched_class;
void init_sched_rt_class(void);
void init_rt_rq(struct rt_rq *rt_rq);
void *malloc(size_t size);			// cannot include stdlib.h

struct cpumask __cpu_online_mask;
struct cpumask __cpu_possible_mask;

void add_task(struct rq *rq)
{
  struct task_struct *t;

  t = malloc(sizeof(struct task_struct));
  memset(t, sizeof(struct task_struct), 0);
  rt_sched_class.enqueue_task(rq, t, ENQUEUE_WAKEUP);
}

void do_schedule(struct rq *rq)
{
  struct task_struct *exec;

  exec = rt_sched_class.pick_task(rq);
  if (exec) {
    printf("Task %d scheduled on CPU %d\n", exec->pid, rq->cpu);
  }
}

int main()
{
  struct rq *rq[4];
  unsigned int i;

  __cpu_online_mask.bits[0] = 0xf;
  __cpu_possible_mask.bits[0] = 0xf;
  init_sched_rt_class();
  for (i = 0; i < 4; i++) {
    rq[i] = malloc(sizeof(struct rq));
    memset(rq[i], sizeof(struct rq), 0);
    init_rt_rq(&rq[i]->rt);
  }

  add_task(rq[0]);
  add_task(rq[0]);
 
  do_schedule(rq[0]);
  do_schedule(rq[1]);
  do_schedule(rq[2]);
  do_schedule(rq[3]);

  return 0;
}
