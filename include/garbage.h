#ifndef MYHEADER
#define MYHEADER

extern int t;
extern void *s[X];

static inline void clear(void) {
    for (int i = 0; i < t; i++) {
        free(s[i]);
        s[i] = 0;
    }
}

#define free(x)
#define malloc(x)(calloc(1, x))
#define calloc(x,y)(atexit(clear),s[t++]=calloc(x, y))
#define realloc(x,y)(c(x),s[t++]=realloc(x,y))

static inline int c(void *x) {
    for (int i = 0; i < t; i++) {
        s[i] = s[i] == x ? NULL : s[i];
    }
    return 1;
}


#endif
