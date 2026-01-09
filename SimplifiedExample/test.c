#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <assert.h>

#include "my_funcs.h"
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
  bool stop;
  unsigned int cnt;
  struct task *t;

  ready_list_init(&my_list);

#if 0
  struct task t1, t2, t3;

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
#else
  stop = false;
  cnt = 0;
  while (!stop) {
    bool insert;

    insert = random_bool(0.5);
    if (insert) {
      t = my_alloc(sizeof(struct task));
      task_init(t, cnt++);
      ready_list_insert(&my_list, t);
      printf("Inserted task%d\n", t->pid);
    } else {
      t = ready_list_get(&my_list);
      if (t) {
        printf("Got task%d\n", t->pid);
        fflush(stdout);
        my_free(t);
      } else {
	printf("Empty!\n");
	fflush(stdout);
      }
    }
    stop = random_bool(0.001);
  }
#endif

  return 0;
}
