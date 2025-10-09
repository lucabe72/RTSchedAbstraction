// From include/linux/cpumask_types.h
/* Don't assign or return these: may not be this big! */
typedef struct cpumask { DECLARE_BITMAP(bits, NR_CPUS); } cpumask_t;

typedef struct cpumask cpumask_var_t[1];

