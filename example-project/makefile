CC = clang
CFLAGS = -Wall -Wpedantic -Wextra -ggdb -I..

run: main
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./main

main: main.c library.c program.h
	$(CC) $(CFLAGS) main.c library.c -o main

clean:
	rm -rf main
