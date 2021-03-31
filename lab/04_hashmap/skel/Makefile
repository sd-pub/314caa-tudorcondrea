CC=clang
CFLAGS=-Wall -Wextra -pedantic -ansi
DEBUG=-g -ggdb -O0 -march=native

build: TestHashtable

TestHashtable: src/TestHashtable.o src/Hashtable_unlinked.o src/LinkedList.o
	$(CC) $(CFLAGS) $(DEBUG) src/TestHashtable.o src/Hashtable_unlinked.o src/LinkedList.o -o TestHashtable


src/Hashtable_unlinked.o: src/Hashtable.h src/Hashtable.c
	$(CC) $(CFLAGS) $(DEBUG) src/Hashtable.c -c -o src/Hashtable_unlinked.o

src/LinkedList.o: src/LinkedList.h src/LinkedList.c
	$(CC) $(CFLAGS) $(DEBUG) src/LinkedList.c -c -o src/LinkedList.o

src/TestHashtable.o: src/TestHashtable.c
	$(CC) $(CFLAGS) $(DEBUG) src/TestHashtable.c -c -o src/TestHashtable.o

run:
	./TestHashtable

clean:
	rm -f src/*.o
	rm -f TestHashtable

