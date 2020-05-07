#include "program.h"

extern void *s[100000];
extern int t;

int main(void)
{
    char *epic = calloc(1, 100);
    strcpy(epic, "lmao");
    puts(epic);

    for (int i = 0; i < 1000; i++)
        malloc(i);

    for (int i = 1000; i < 2000; i++) {
        int *fuck = malloc(i);
        free(fuck);
    }

    for (int i = 0; i < 100; i++) {
        free(epic);
        free(epic);
    }

    char *small = strcpy(realloc(NULL, 10), "hello");
    puts(small);
    clean(small);
    small = strcpy(realloc(small, 1000), "bittttttttchhhhhhhhyyyyy");
    puts(small);

    char *paga = pagan();

#undef free

    for (int i = 0; i < t; i++)
        free(s[i]), s[i] = 0;

    return 0;
}
