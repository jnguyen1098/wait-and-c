CC = clang
CFLAGS = -Wall -Wpedantic -Wextra -ggdb -Iinclude
VFLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes

run: bin/main
	./bin/main

valgrind: bin/main
	valgrind $(VFLAGS) ./bin/main

bin/main: obj/main.o obj/library.o include/program.h
	$(CC) $(CFLAGS) obj/library.o obj/main.o -o bin/main

obj/main.o: src/main.c include/program.h
	$(CC) $(CFLAGS) -c src/main.c -o obj/main.o

obj/library.o: src/library.c include/program.h
	$(CC) $(CFLAGS) -c src/library.c -o obj/library.o


expand: src/main_e.c src/library_e.c

src/main_e.c: src/main.c include/program.h
	$(CC) $(CFLAGS) src/main.c -E -P -o src/main_e.c

src/library_e.c: src/library.c include/program.h
	$(CC) $(CFLAGS) src/library.c -E -P -o src/library_e.c


clean:
	rm -rf obj/*.o
	rm -rf bin/main
