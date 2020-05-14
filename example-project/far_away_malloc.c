#include <stdlib.h>
#include <string.h>

/* one line install */
#include "../garbage.h"

char *this_malloc_comes_from_another_file(void)
{
    for (int i = 0; i < 1000; i++)
        malloc(12000);
    char *pag = malloc(1000);
    return strcpy(pag, "hello from the other side");
}
