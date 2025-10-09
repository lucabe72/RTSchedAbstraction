static inline void raw_spin_lock(raw_spinlock_t *lock) {}
static inline void raw_spin_unlock(raw_spinlock_t *lock) {}
static inline int double_lock_balance(struct rq *this_rq, struct rq *busiest) {return 1;}
static inline void double_unlock_balance(struct rq *this_rq, struct rq *busiest)
 {}


