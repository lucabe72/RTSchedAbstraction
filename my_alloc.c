#include <stdlib.h>
#include <string.h>
#include "my_alloc.h"

#if 0
struct task_struct *alloc_task(void)
{
  struct task_struct *t;

  t = malloc(sizeof(struct task_struct));
  memset(t, sizeof(struct task_struct), 0);

  return t;
}

struct rq *alloc_rq(void)
{
  struct rq *rq;

  rq = malloc(sizeof(struct rq));
  memset(rq, sizeof(struct rq), 0);

  return rq;
}
#else
void *my_alloc(unsigned int size)
{
  void *p;

  p = malloc(size);
  memset(p, 0, size);

  return p;
}
#endif
