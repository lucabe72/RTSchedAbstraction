struct plist_head         {};
struct plist_node         {};

//FIXME: these are all empty stubs!
static inline void plist_head_init(struct plist_head *head) { }
static inline int plist_head_empty(const struct plist_head *head)
{
  return 0;
}
static inline void plist_node_init(struct plist_node *node, int prio)
{
}
static void plist_add(struct plist_node *node, struct plist_head *head)
{
}
static void plist_del(struct plist_node *node, struct plist_head *head)
{
}
//#define plist_first_entry(head, type, member)  \
//        container_of(plist_first(head), type, member)
#define plist_first_entry(head, type, member) NULL
#define plist_for_each_entry(pos, head, mem) while(0)

