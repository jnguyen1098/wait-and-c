CC = clang
CFLAGS = -Wall -Wpedantic -Wextra -ggdb -I.
VFLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes

valgrind: main
	valgrind $(VFLAGS) ./main

main: main.o library.o program.h
	$(CC) $(CFLAGS) library.o main.o -o main

main.o: main.c program.h
	$(CC) $(CFLAGS) -c main.c -o main.o

library.o: library.c program.h
	$(CC) $(CFLAGS) -c library.c -o library.o

clean:
	rm -rf *.o main
