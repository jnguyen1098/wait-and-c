#include <stdlib.h>
#include <sys/wait.h>

void *ptr, *addrs[100000];
size_t head;

static inline void f() {
    for (size_t i = 0; i < head; i++)
        addrs[i] = (free(addrs[i]), NULL);
}

#define free(x) if(x){}
#define malloc(x)((signal(SIGSEGV,f),(atexit(f),addrs[head++]=malloc(x))))
#define calloc(x,y)((signal(SIGSEGV,f),(atexit(f),addrs[head++]=calloc(x, y))))
#define realloc(x,y)((x?__extension__({ptr=x;for(size_t i=0;i<head;i++)addrs[i]==ptr?addrs[i]=0:0;signal(SIGSEGV,f);atexit(f);}):(signal(SIGSEGV,f),atexit(f))),addrs[head++]=realloc(x,y))
