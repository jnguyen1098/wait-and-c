#include <stdlib.h>

// ptr is used for realloc
// addrs is used to store every address
void *ptr, *addrs[100000];

// keeps track of how many ptrs we're at
size_t head;

// cleanup function. the __attribute__ designates
// that the function will execute on exit
__attribute__((destructor))
static inline void cleanup() {
    for (size_t i = 0; i < head; i++)
        addrs[i] = (free(addrs[i]), NULL);
}

// remove all free() calls
#define free(x) if(x){}

// push addr on malloc and return to caller
#define malloc(x)(addrs[head++] = malloc(x))

// push addr on calloc and return to caller
#define calloc(x,y)(addrs[head++] = calloc(x,y))

// fix addr table on realloc
#define realloc(x,y)((                          \
    x ? __extension__({                         \
        ptr = x;                                \
        for(size_t i = 0; i < head; i++)        \
            addrs[i] == ptr ? addrs[i] = 0 : 0; \
    }) : (void)0),                              \
    addrs[head++] = realloc(x,y)                \
)
