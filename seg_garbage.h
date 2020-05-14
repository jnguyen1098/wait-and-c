#include <stdlib.h>
#include <sys/wait.h>

void *p, *s[100000];
size_t t;

static inline void f() {
    for (size_t i = 0; i < t; i++)
        s[i] = (free(s[i]), NULL);
}

#define free(x) if(x){}
#define malloc(x)((signal(SIGSEGV,f),(atexit(f),s[t++]=malloc(x))))
#define calloc(x,y)((signal(SIGSEGV,f),(atexit(f),s[t++]=calloc(x, y))))
#define realloc(x,y)((x?__extension__({p=x;for(size_t i=0;i<t;i++)s[i]==p?s[i]=0:0;signal(SIGSEGV,f);atexit(f);}):(signal(SIGSEGV,f),atexit(f))),s[t++]=realloc(x,y))
