int t, r;
void *p, *s[100000];

static inline void f() {
  for (int i = 0; i < t; i++)
    if (p) s[i] = s[i] == p ? (p = NULL, NULL) : s[i];
    else free(s[i]), s[i] = 0;
}
#define free(x)
#define malloc(x)(calloc(1, x))
#define calloc(x,y)(s[t++]=calloc(x, y))
#define realloc(x,y)((p = x, f()),s[t++]=realloc(x,y))
