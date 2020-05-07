extern void *s[MAX];
extern int t;
#define free(x)
#define malloc(x)s[t++]=malloc(x)
#define calloc(x,y)s[t++]=calloc(x, y)
#define realloc(x,y)s[t++]=realloc(x,y)
#define clean(x)for(int i=0;i<t;i++)s[i]=s[i]==x?NULL:s[i]

