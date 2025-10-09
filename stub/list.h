struct list_head {
  struct list_head *next, *prev;
};

static inline void INIT_LIST_HEAD(struct list_head *list)
{
	list->next = list;
	list->prev = list;
}


static inline void list_del_init(struct list_head *entry)
{
}
static inline int list_empty(const struct list_head *head)
{
  return 0;
}
static inline void list_add(struct list_head *new, struct list_head *head)
{
}
static inline void list_add_tail(struct list_head *new, struct list_head *head)
{
}
static inline void list_move(struct list_head *list, struct list_head *head)
{
}
static inline void list_move_tail(struct list_head *list, struct list_head *head)
{
}
#define list_entry(ptr, type, member) NULL
