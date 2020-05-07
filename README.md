# Wait and C

Here's my attempt to make a one-size-fits-all solution for C memory management.
Every call to a library allocation function (`malloc`, `calloc`, `realloc`)
gets intercepted, causing the return addresses to enter a makeshift address
stack.

At the end of the program, each address in this stack is freed by a for loop
(which I included in the demonstration). 

## How to use

Just run `make` and everything will compile, followed by a run using the
`valgrind` memory debugger with useful flags enabled.

If you're making modifications, be sure to also run `make clean`.
