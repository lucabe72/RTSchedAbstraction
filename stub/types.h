#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef int64_t  s64;
typedef uint64_t u64;
#ifndef __pid_t_defined
typedef int pid_t;
#define __pid_t_defined
#endif

// From include/linux/types.h
#define DECLARE_BITMAP(name,bits) \
        unsigned long name[BITS_TO_LONGS(bits)]

// From task.h
/*
 * Define the task command name length as enum, then it can be visible to
 * BPF programs.
 */
enum {
        TASK_COMM_LEN = 16,
};



