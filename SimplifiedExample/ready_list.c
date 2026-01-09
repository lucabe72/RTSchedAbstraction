struct ready_list {
	struct list_head queue;
	unsigned int n_tasks;
};

struct task {
  struct list_head l;
  int pid;
  /* ... */
};

void ready_list_init(struct ready_list *l)
{
  l->n_tasks = 0;
  INIT_LIST_HEAD(&l->queue);
}

void ready_list_insert(struct ready_list *l, struct task *t)
{
  list_add(&t->l, &l->queue);
  l->n_tasks++;
}

struct task *ready_list_get(struct ready_list *l)
{
  struct task *t;

  if (list_empty(&l->queue)) {
    assert(l->n_tasks == 0);

    return NULL;
  }

  t = list_entry(l->queue.next, struct task, l);
  list_del_init(&t->l);
  l->n_tasks--;

  return t;
}

