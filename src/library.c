#include "program.h"
#include "cheat.h"

char *this_malloc_comes_from_the_far_lands(void)
{
    for (int i = 0; i < 1000; i++)
        malloc(10000);
    char *pag = malloc(1000);
    return strcpy(pag, "hello from the other side");
}
