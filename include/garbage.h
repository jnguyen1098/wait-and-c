void *p, *s[100000];
size_t t;

static inline void f() {
    for (size_t i = 0; i < t; i++)
        free(s[i]);
}

#define free(x)
#define malloc(x)(s[t++]=malloc(x))
#define calloc(x,y)(s[t++]=calloc(x, y))
#define realloc(x,y)((x?__extension__({for(size_t i=0;i<t;i++)s[i]==p?s[i]=0:0;}):(void)0),s[t++]=realloc(x,y))

