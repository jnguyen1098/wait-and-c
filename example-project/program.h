#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include "../garbage.h"           // normal garbage collector
//#include "../garbage_seg.h"       // garbage.h but with segfault support
//#include "../garbage_fast.h"      // garbage.h butwithout atexit()
#include "../garbage_expanded.h"  // garbage.h but expanded with comments

char *this_malloc_comes_from_the_far_lands(void);
