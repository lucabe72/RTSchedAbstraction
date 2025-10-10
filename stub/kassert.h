#include <assert.h>

#define BUG_ON(x) assert(!(x))
#define WARN_ON(x)      (assert(!(x)), (!(x)))
#define WARN_ON_ONCE(x) (assert(!(x)), (!(x)))
