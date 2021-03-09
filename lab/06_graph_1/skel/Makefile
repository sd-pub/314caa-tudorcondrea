CC=gcc
CFLAGS=-Wall -Wextra -pedantic -ansi
DEBUG=-g -ggdb -O0 -march=native -std=c99

build: Test

Test: src/Test.o src/Queue_unlinked.o src/Stack_unlinked.o src/LinkedList.o src/MatrixGraph_unlinked.o src/ListGraph_unlinked.o
	$(CC) $(CFLAGS) $(DEBUG) src/Test.o src/Queue_unlinked.o src/Stack_unlinked.o src/LinkedList.o src/MatrixGraph_unlinked.o src/ListGraph_unlinked.o -o Test

src/MatrixGraph_unlinked.o: src/MatrixGraph.c src/MatrixGraph.h
	$(CC) $(CFLAGS) $(DEBUG) src/MatrixGraph.c -c -o src/MatrixGraph_unlinked.o

src/ListGraph_unlinked.o: src/ListGraph.c src/ListGraph.h
	$(CC) $(CFLAGS) $(DEBUG) src/ListGraph.c -c -o src/ListGraph_unlinked.o

src/Queue_unlinked.o: src/Queue.h src/Queue.c
	$(CC) $(CFLAGS) $(DEBUG) src/Queue.c -c -o src/Queue_unlinked.o

src/Stack_unlinked.o: src/Stack.h src/Stack.c
	$(CC) $(CFLAGS) $(DEBUG) src/Stack.c -c -o src/Stack_unlinked.o

src/LinkedList.o: src/LinkedList.h src/LinkedList.c
	$(CC) $(CFLAGS) $(DEBUG) src/LinkedList.c -c -o src/LinkedList.o

src/Test.o: src/Test.c
	$(CC) $(CFLAGS) $(DEBUG) src/Test.c -c -o src/Test.o

run:
	./Test

clean:
	rm src/*.o
	rm Test