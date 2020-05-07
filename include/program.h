#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define X 100000
void *s[X]; int t;
#include "garbage.h"

char *this_malloc_comes_from_the_far_lands(void);
