#include <stdlib.h>

char *ram;
size_t brk;

void __attribute__((constructor)) lmao(void) {
    !ram ? atexit(lmao), ram = calloc(1, 100000) : free(ram);
}

#define calloc(x,y)(malloc(x*y)) 
#define malloc(x)(void *)(&ram[brk] + x >= &ram[100000 - 1] ? NULL : (brk += x, &ram[brk - x]))
#define free(x)
