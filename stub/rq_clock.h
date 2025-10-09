static inline u64 rq_clock(struct rq *rq)
{
        return rq->clock;
}

static inline u64 rq_clock_task(struct rq *rq)
{
        return rq->clock_task;
}

static inline u64 rq_clock_pelt(struct rq *rq)
{
        return rq->clock_pelt - rq->lost_idle_time;
}
