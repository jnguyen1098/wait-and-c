void *p, *s[100000];
size_t t;

static inline void f() {

#if 1
    for (size_t i = 0; i < t; i++)
        s[i] = p && s[i] == p ? (p = NULL, NULL) : (free(s[i]), NULL);
#endif

#if 0
    for (size_t i = 0; i < t; i++) {
        if (p && s[i] == p)
            s[i] = p = NULL;
        else
            s[i] = (free(s[i]), NULL);
    }
#endif


#if 0
    for (unsigned i = 0; i < t; i++) {
        if (p) {
            if (s[i] == p) {
                s[i] = NULL;
                p = NULL;
            }
        }
        else {
            free(s[i]);
            s[i] = NULL;
        }
    }
#endif
}

#define free(x)
#define malloc(x)(s[t++]=malloc(x))
#define calloc(x,y)(s[t++]=calloc(x, y))
#define realloc(x,y)((p = x, f()),s[t++]=realloc(x,y))
