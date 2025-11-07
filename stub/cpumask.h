#include "cpumask_types.h"

/**
 * cpumask_bits - get the bits in a cpumask
 * @maskp: the struct cpumask *
 *
 * You should only assume nr_cpu_ids bits of this mask are valid.  This is
 * a macro so it's const-correct.
 */
#define cpumask_bits(maskp) ((maskp)->bits)


// From include/linux/cpumask.h

static inline void cpu_max_bits_warn(unsigned int cpu, unsigned int bits)
{
        WARN_ON_ONCE(cpu >= bits);
}

/* verify cpu argument to cpumask_* operators */
static inline unsigned int cpumask_check(unsigned int cpu)
{       
        cpu_max_bits_warn(cpu, NR_CPUS);
        return cpu;
}

/**
 * cpumask_set_cpu - set a cpu in a cpumask
 * @cpu: cpu number (< nr_cpu_ids)
 * @dstp: the cpumask pointer
 */
static inline void cpumask_set_cpu(unsigned int cpu, struct cpumask *dstp)
{
        set_bit(cpumask_check(cpu), cpumask_bits(dstp));
}

/**
 * cpumask_clear_cpu - clear a cpu in a cpumask
 * @cpu: cpu number (< nr_cpu_ids)
 * @dstp: the cpumask pointer
 */
static inline void cpumask_clear_cpu(int cpu, struct cpumask *dstp)
{
        clear_bit(cpumask_check(cpu), cpumask_bits(dstp));
}

/**
 * cpumask_test_cpu - test for a cpu in a cpumask
 * @cpu: cpu number (< nr_cpu_ids)
 * @cpumask: the cpumask pointer
 *
 * Return: true if @cpu is set in @cpumask, else returns false
 */
static inline bool cpumask_test_cpu(int cpu, const struct cpumask *cpumask)
{
        return test_bit(cpumask_check(cpu), cpumask_bits((cpumask)));
}

/**
 * cpumask_clear - clear all cpus (< nr_cpu_ids) in a cpumask
 * @dstp: the cpumask pointer
 */
static inline void cpumask_clear(struct cpumask *dstp)
{
        bitmap_zero(cpumask_bits(dstp), NR_CPUS);
}

/**
 * cpumask_next - get the next cpu in a cpumask
 * @n: the cpu prior to the place to search (i.e. return will be > @n)
 * @srcp: the cpumask pointer
 *
 * Return: >= nr_cpu_ids if no further cpus set.
 */
static inline unsigned int cpumask_next(int n, const struct cpumask *srcp)
{
        /* -1 is a legal arg here. */
        if (n != -1)
                cpumask_check(n);
        return find_next_bit(cpumask_bits(srcp), NR_CPUS, n + 1);
}

/* CONFIG_CPUMASK_OFFSTACK is not devined, cpumasks are on stack! */
static inline bool zalloc_cpumask_var_node(cpumask_var_t *mask, gfp_t flags, int node)
{
        cpumask_clear(*mask);
        return true;
}

extern struct cpumask __cpu_online_mask;
extern struct cpumask __cpu_possible_mask;
#define cpu_online_mask   ((const struct cpumask *)&__cpu_online_mask)
#define cpu_possible_mask ((const struct cpumask *)&__cpu_possible_mask)
static inline bool cpu_online(unsigned int cpu)
{
        return cpumask_test_cpu(cpu, cpu_online_mask);
}

//FIXME: implement something that does not fail...
static inline unsigned int cpumask_any_and_distribute(const struct cpumask *src1p, const struct cpumask *src2p)
{
  return NR_CPUS + 1;
}
static inline unsigned int cpumask_any_distribute(const struct cpumask *srcp)
{
  return NR_CPUS + 1;
}

//FIXME: check the definition... it uses a "1 ? (bitmap) : ..."???
#define to_cpumask(bitmap) ((struct cpumask *)(bitmap))


/**
 * cpumask_copy - *dstp = *srcp
 * @dstp: the result
 * @srcp: the input cpumask
 */
static inline void cpumask_copy(struct cpumask *dstp, const struct cpumask *srcp)
{
        bitmap_copy(cpumask_bits(dstp), cpumask_bits(srcp), NR_CPUS);
}


/**
 * for_each_cpu - iterate over every cpu in a mask
 * @cpu: the (optionally unsigned) integer iterator
 * @mask: the cpumask pointer
 *
 * After the loop, cpu is >= nr_cpu_ids.
 */
#define for_each_cpu(cpu, mask)                         \
        for_each_set_bit(cpu, cpumask_bits(mask), NR_CPUS)

//#define for_each_possible_cpu(cpu) for_each_cpu((cpu), cpu_possible_mask)
#define for_each_possible_cpu(cpu) for(cpu = 0; cpu < NR_CPUS; cpu++)

