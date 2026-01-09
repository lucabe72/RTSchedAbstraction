#include <stdio.h>
#include <stddef.h>
#include <assert.h>

#include "src/container_of.h"
#include "stub/list.h"

#include "ready_list.c"

void task_init(struct task *t, int pid)
{
  INIT_LIST_HEAD(&t->l);
  t->pid = pid;
}

int main()
{
  struct ready_list my_list;
  struct task t1, t2, t3, *t;

  ready_list_init(&my_list);
  task_init(&t1, 0);
  task_init(&t2, 1);
  task_init(&t3, 2);

  ready_list_insert(&my_list, &t1);
  ready_list_insert(&my_list, &t2);
  ready_list_insert(&my_list, &t3);

  t = ready_list_get(&my_list);
  while (t) {
    printf("Got task%d\n", t->pid);
    fflush(stdout);
    t = ready_list_get(&my_list);
  }

  return 0;
}
