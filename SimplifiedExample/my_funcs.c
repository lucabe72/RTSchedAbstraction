#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "my_funcs.h"

bool random_bool(double probability)
{
    return rand() < probability * ((double)RAND_MAX + 1.0);
}

void *my_alloc(unsigned int size)
{
  void *p;

  p = malloc(size);
  memset(p, 0, size);

  return p;
}

void my_free(void *p)
{
  free(p);
}

