#include <stdbool.h>


//Simplified definitions from include/asm-generic/bitops/generic-non-atomic.h

#define BITS_PER_LONG		(sizeof(long) * 8)
#define BIT_MASK(nr)            ((unsigned long)1 << ((nr) % BITS_PER_LONG))
#define BIT_WORD(nr)            ((nr) / BITS_PER_LONG)

static inline void __set_bit(unsigned long nr, unsigned long *addr)
{
        unsigned long mask = BIT_MASK(nr);
        unsigned long *p = addr + BIT_WORD(nr);

        *p  |= mask;
}
// Let's ignore atomicity, for now
#define set_bit __set_bit

static inline void __clear_bit(unsigned long nr, unsigned long *addr)
{
        unsigned long mask = BIT_MASK(nr);
        unsigned long *p = addr + BIT_WORD(nr);

        *p &= ~mask;
}
#define clear_bit __clear_bit


static inline bool test_bit(unsigned long nr, const unsigned long *addr)
{
        return 1UL & (addr[BIT_WORD(nr)] >> (nr & (BITS_PER_LONG-1)));
}


static inline unsigned int __ffs(unsigned long word)
{
        unsigned int num = 0;

        if ((word & 0xffffffff) == 0) {
                num += 32;
                word >>= 32;
        }
        if ((word & 0xffff) == 0) {
                num += 16;
                word >>= 16;
        }
        if ((word & 0xff) == 0) {
                num += 8;
                word >>= 8;
        }
        if ((word & 0xf) == 0) {
                num += 4;
                word >>= 4;
        }
        if ((word & 0x3) == 0) {
                num += 2;
                word >>= 2;
        }
        if ((word & 0x1) == 0)
                num += 1;
        return num;
}

static inline int sched_find_first_bit(const unsigned long *b)
{
        if (b[0])
                return __ffs(b[0]);
        return __ffs(b[1]) + 64;
}

//from include/linux/bitops.h
#define __KERNEL_DIV_ROUND_UP(n, d) (((n) + (d) - 1) / (d))
#define BITS_TO_LONGS(nr)       __KERNEL_DIV_ROUND_UP(nr, sizeof(long) * 8)


