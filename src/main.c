#include "program.h"

int main(void)
{
    /* calloc leakage */
    char *epic = calloc(1, 100);
    strcpy(epic, "memory is overrated");
    puts(epic);

    /* malloc leakage */
    for (int i = 0; i < 1000; i++)
        malloc(i);

    /* free() is completely blocked off */
    for (int i = 1000; i < 2000; i++) {
        int *fuck = malloc(i);
        free(fuck);
        if (fuck) fuck = NULL;
    }

    /* double freeing is bad? how about 1000? */
    for (int i = 0; i < 1000; i++)
        free(epic);

    /* realloc */
    char *small = strcpy(realloc(NULL, 10), "g force");
    puts(small);
    small = strcpy(realloc(small, 1000), "test test t estset set s");
    puts(small);

    /* calling malloc using another file's function */
    char *pagakfdsgjhalskghaslggagjkh = this_malloc_comes_from_the_far_lands();
    if (pagakfdsgjhalskghaslggagjkh)
        ;

    return 0;
}
