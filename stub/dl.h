#define MAX_DL_PRIO		0

static inline bool dl_prio(int prio)
{
        return prio < MAX_DL_PRIO;
}

/*
 * Returns true if a task has a priority that belongs to DL class. PI-boosted
 * tasks will return true. Use dl_policy() to ignore PI-boosted tasks.
 */
static inline bool dl_task(struct task_struct *p)
{
        return dl_prio(p->prio);
}
