# Wait and C

This is my attempt to make a really limited but functional garbage collector for C. Every call to an allocation function (`malloc`, `calloc`, `realloc`) gets intercepted and recorded in an array of addresses. At program termination, each address in this stack is freed. I had a lot of fun abusing the C preprocessor in making this. _Enjoy!_

Installation is very seamless: you just have to add and `#include` a new `.h` file to your project—nothing else. All of your existing `free()` calls are removed, so this can even help fix broken projects with corrupted `free()`s.

## How to install this onto an existing C project

Put the line `#include "garbage.h"` (or whatever name) in every file that uses an alloc function.

## Demonstration

The `main.c` file contains many different ways to mess up memory management; from freeing the same pointer a trillion times to creating unreferenced chunks of memory, Wait-and-C is able to track and free all memory regardless of what you throw at it. To run this cursed `main.c`, just run `make`.

## ⚠️⚠️⚠️ Warnings ⚠️⚠️⚠️

### **Don't use non-standard allocation functions**
**DO NOT** use deprecated dynamic allocation functions (such as `valloc()`, `pvalloc()`, `aligned_alloc()`, `alloca()`, among other disappoinments)—I do not intercept these calls!!! Unless you have a page fault fetish, you don't need `valloc()` or whatever.

### **FILEs**
You're on your own when it comes to calling `fopen()` on `FILE` pointers. I'm not doubling this repo's code just to make sure the your `fopen()` is matched up with the `fclose()` you forgot to use. Use `valgrind` to aid you in your soul search if need be.

### **Don't use `strdup()`**
I've looked long and hard, and the only non-`fopen()` function I know of that hides its heap allocation is `strdup()` (and in a way it is [hated](https://stackoverflow.com/questions/12984948/why-is-strdup-considered-to-be-evil) because of this principle). The collector won't be able to note the allocation. That being said, it's not even a standard function and can only be called by compiling with flags such as `-std=gnu11`, `-std=gnu99`, etc. so as long as you compile with normal `-std=Cwhatever_version_you_prefer`  flags, you will never run into this issue.

## 🥺🥺🥺 How does it work? 🥺🥺🥺

### The Variables `p`, `s`, and `t`

The `f()` function is a `static` `inline` function that `NULL`s out addresses as it `free()`s them; `static`, meaning its scope is limited to its translation unit, and `inline`, meaning its position in code is (usually) directly in the calling scope, rather than jumping to the function. Both keywords are needed in order for this project to only exist in a single file (I didn't even know you could put functions in `.h` files until now).

`s` is the array of `void *` pointers. It keeps track of every allocation, and `t` represents the index of the latest position of the array. When you call `realloc()`, I run an inline `for` loop to `NULL` out the existing address, so I can no longer rely on `NULL` as a sentinel value. Hence `t`.

### The Preprocessor Macros

```c
#define free(x) if(x){}
```

This removes all existing `free()` calls, but because this preprocessor macro occurs after `f()`, it doesn't affect the actual `free()`s in `f()`. Just the user's `free()`s thereafter. It's because of this line that lets the collector fix basic double `free()` problems. At first it was `#define free(x)`, but when paired with strict compilation environments, removing `free()` sometimes caused `unused variable` errors. Usually not an issue, though, but I wanted to cover all bases.

```c
#define malloc(x)(atexit(f),s[t++]=malloc(x))
#define calloc(x,y)(atexit(f),s[t++]=calloc(x,y))
```

Every time `malloc()` or `calloc()` are called, the macro runs `atexit(f)`, which tells the process to run the `f()` function at the end of program runtime. This negatively detriments performance (in my testing), but as a proof-of-concept I had to leave it in for portability. In reality, if you controlled the `main()`, you should just call `atexit(f)` once, and move on with your life. `garbage_fast.h` has these `atexit(f)` calls removed, so please use that if you want your programs to run slightly faster. I just kept it in to account for the case of dynamically-linked program `main()`s that the programmer didn't have access to (`atexit()` covers the entire process, so if you are running another person's compiled binary, `atexit()` will intercept over to that).

The second part, `s[t++]=malloc(x)` (or `s[t++]=calloc(x,y)`), is analogous to pushing to an array (or stack if you're fancy). It pushes the result of `malloc()`/`calloc()` to array `s`, increments the `t` "pointer", and then returns that address as the result of the expression.

`char *word = malloc(x);`, when expanded with the above `#define`, is equivalent to:

```c
char *word;
atexit(f);
s[t] = malloc(x);
word = s[t];
t++;
```

Likewise, `char *word = calloc(x,y)` is equivalent to:

```c
char *word;
atexit(f);
s[t] = calloc(x, y);
word = s[t];
t++;
```

In C, the comma operator `,` can be used to cram multiple expressions into one statement. When using such an operator, only the final operand is used. So, in this statement

```c
char *word = (printf("this statement is useless"), malloc(100));
```

the return value of `printf()` (which is the number of characters outputted) is ignored. That was how I managed to shove the `atexit(f)` call into the macros. Adding spacing emphasizes this:

```c
#define malloc(x)   (  atexit(f),  s[t++] = malloc(x)   )
#define calloc(x,y) (  atexit(f),  s[t++] = calloc(x,y) )
```

Commented and spaced-out versions of these files are also included in the repo.

```c
#define realloc(x,y)((x?__extension__({p=x;for(size_t i=0;i<t;i++)s[i]==p?s[i]=0:0;atexit(f);}):atexit(f)),s[t++]=realloc(x,y))
```

This is pretty jammed. Here is the spaced version.

```c
#define realloc(x, y)\
    (__extension__({                            \
        atexit(f);                              \
        if (x) {                                \
            p = x;                              \
            for (size_t i = 0; i < t; i++) {    \
                if (s[i] == p)                  \
                    s[i] = NULL;                \
            }                                   \
        }                                       \
        s[t++]=realloc(x,y);                    \
    }))
```