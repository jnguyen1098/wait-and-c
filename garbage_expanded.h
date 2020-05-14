#include <stdlib.h>

void *ptr, *addrs[100000];
size_t head;

static inline void cleanup() {
    for (size_t i = 0; i < head; i++)
        addrs[i] = (free(addrs[i]), NULL);
}

#define free(x) if(x){}

// call atexit() on malloc and push addr
#define malloc(x)(__extension__({       \
    atexit(cleanup);                    \
    addrs[head++] = malloc(x);          \
}))

// call atexit() on calloc and push addr
#define calloc(x,y)(__extension__({     \
    atexit(cleanup);                    \
    addrs[head++] = calloc(x,y);        \
}))

// call atexit() on realloc, clear old
// address if possible, then call realloc
#define realloc(x,y)(__extension__({    \
    size_t i;                           \
    if (!atexit(cleanup) && x) {        \
        for (i = 0; i < head; i++) {    \
            if (addrs[i] == x)          \
                addrs[i] = NULL;        \
        }                               \
    }                                   \
    addrs[head++] = realloc(x,y);       \
}))

