#include <stdlib.h>

void *ptr, *addrs[100000];
size_t head;

static inline void cleanup() {
    for (size_t i = 0; i < head; i++)
        addrs[i] = (free(addrs[i]), NULL);
}

#define free(x) if(x){}
#define malloc(x)(atexit(cleanup),addrs[head++]=malloc(x))
#define calloc(x,y)(atexit(cleanup),addrs[head++]=calloc(x,y))
#define realloc(x,y)((x?__extension__({ptr=x;for(size_t i=0;i<head;i++)addrs[i]==ptr?addrs[i]=0:0;atexit(cleanup);}):atexit(cleanup)),addrs[head++]=realloc(x,y))
