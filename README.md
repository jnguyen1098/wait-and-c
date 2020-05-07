# Wait and C

Here's my attempt to make a one-size-fits-all solution for C memory management.
Every call to a library allocation function (e.g. `malloc`, `calloc`, `realloc`) gets intercepted and recorded in an array of addresses. At program termination, each address in this stack is freed. Quick and easy garbage management. Whether you stealthily install this into an existing project or just want to see a demonstration, I had a lot of fun abusing the shit out of the C preprocessor. _Enjoy!_

Installation is very seamless: you just have to add and `#include` a new `.h` file to your project—nothing else! (You can keep all your existing `free()` calls as they are `NOP`'d). In addition to that, I made a few quality-of-life changes:

- You can now `free()` already-`free()`'d pointers without corrupting memory
- All of your existing `malloc()` calls are now `calloc()` calls (stop reading garbage!!!)

## How to install this onto an existing C project
Installation will depend on your setup, but I made the process as easy as possible.

### **Scenario One**: every C file in your project uses the same `.h` file and you're lazy
This is truly a pog moment, because now you can literally just download `garbage.h`, put it where your compiler can see it, and then put the line `#include "garbage.h"` in your personal `.h` file. Now it'll be `#include`d in all of your source files regardless of whether a heap allocation function is called (no, it's not harmful to include `garbage.h` even if you don't use these functions).

### **Scenario Two**: the above, except you're not lazy and want to be ```S T E A L T H Y```
Instead of `#include "garbage.h"` or whatever name you chose for it, paste the contents of the file directly into your existing `.h` file. The `#include` macro is literally just "paste the contents of this file", so by doing this yourself you won't have an extra `.h` file.

### **Scenario Three**: everyone else
You could do any combination of the above to be honest. As long as the `#include "garbage.h"` line or the contents of the file are present in every `.c` file that calls a heap allocation function, you can't really go wrong. 

## Demonstration

The `main.c` file contains many different ways to mess up memory management; from freeing the same pointer a trillion times to creating unreferenced chunks of memory, Wait-and-C is able to track and free all memory regardless of what you throw at it. To run this cursed `main.c`, just run `make` and watch `valgrind` report back.

## 🥺🥺🥺 How does it work? 🥺🥺🥺

### test

## ⚠️⚠️⚠️ Warnings ⚠️⚠️⚠️

### **FILE \*fp = fopen("fuck off", "r")**
You're on your own when it comes to calling `fopen()` on `FILE` pointers. I'm not doubling this repo's code just to make sure the your `fopen()` is matched up with the `fclose()` you forgot to use. Use `valgrind` to aid you in your soul search if need be.

### **Don't fucking use `strdup()` you simp**
**Do not use `strdup()`**! I've looked long and hard, and the only non-`fopen()` function I know of that hides its heap allocation is `strdup()` (and in a way it is [hated](https://stackoverflow.com/questions/12984948/why-is-strdup-considered-to-be-evil) because of this principle). That being said, it's not even a standard function and can only be called by compiling with flags such as `-std=gnu11`, `-std=gnu99`, etc. so as long as you compile with normal `-std=Cwhatever_version_you_prefer`  flags, you will never run into this issue.

### **You `alloca()`n't be fucking serious**
**DO NOT** use deprecated dynamic allocation functions (such as `valloc()`, `pvalloc()`, `aligned_alloc()`, `alloca()`, among other disappoinments)—I do not intercept these calls!!! Unless you have a page fault fetish, you don't need `valloc()` or whatever.