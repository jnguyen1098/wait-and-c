#include <stdlib.h>

void *p, *s[100000];
size_t t;

static inline void f() {
    for (size_t i = 0; i < t; i++)
        s[i] = (free(s[i]), NULL);
}

#define free(x) if(x){}
#define malloc(x)(atexit(f),s[t++]=malloc(x))
#define calloc(x,y)(atexit(f),s[t++]=calloc(x, y))
#define realloc(x,y)((x?__extension__({p=x;for(size_t i=0;i<t;i++)s[i]==p?s[i]=0:0;atexit(f);}):atexit(f)),s[t++]=realloc(x,y))
