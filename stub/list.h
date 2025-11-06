struct list_head {
  struct list_head *next, *prev;
};

static inline void INIT_LIST_HEAD(struct list_head *list)
{
	list->next = list;
	list->prev = list;
}

static inline void __list_del(struct list_head * prev, struct list_head * next)
{
	next->prev = prev;
	prev->next = next;
}
static inline void __list_del_entry(struct list_head *entry)
{
	__list_del(entry->prev, entry->next);
}
static inline void list_del_init(struct list_head *entry)
{
	__list_del_entry(entry);
	INIT_LIST_HEAD(entry);
}

static inline int list_empty(const struct list_head *head)
{
  return head->next == head;
}

static inline void __list_add(struct list_head *new,
			      struct list_head *prev,
			      struct list_head *next)
{
  next->prev = new;
  new->next = next;
  new->prev = prev;
  prev->next = new;
}
static inline void list_add(struct list_head *new, struct list_head *head)
{
  __list_add(new, head, head->next);
}

static inline void list_add_tail(struct list_head *new, struct list_head *head)
{
  __list_add(new, head->prev, head);
}

static inline void list_move(struct list_head *list, struct list_head *head)
{
  __list_del_entry(list);
  list_add(list, head);
}
static inline void list_move_tail(struct list_head *list, struct list_head *head)
{
  __list_del_entry(list);
  list_add_tail(list, head);
}

#define list_entry(ptr, type, member) container_of(ptr, type, member)
