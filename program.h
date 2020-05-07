#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define free(x)
#define calloc(x,y)s[t++]=calloc(x, y)
#define malloc(x)s[t++]=malloc(x)
#define clean(x)for(int i=0;i<t;i++)s[i]=s[i]==x?NULL:s[i]
#define realloc(x,y)s[t++]=realloc(x,y)

void *s[100000];
int t;

char *pagan(void);
