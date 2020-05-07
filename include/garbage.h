#ifndef MYHEADER
#define MYHEADER

int t;
void *s[100000];

extern int t;
extern void *s[100000];

static inline void f(void) {
    for (int i = 0; i < t; i++)
        free(s[i]), s[i] = 0;
}

static inline void c(void *x) {
    for (int i = 0; i < t; i++)
        s[i] = s[i] == x ? NULL : s[i];
}

#define free(x)
#define malloc(x)(calloc(1, x))
#define calloc(x,y)(s[t++]=calloc(x, y))
#define realloc(x,y)(c(x),s[t++]=realloc(x,y))
#endif
