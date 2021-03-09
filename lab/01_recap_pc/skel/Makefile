CC=clang
CFLAGS=-Wall -Wextra -pedantic -ansi
DEBUG=-g -ggdb -O0 -march=native

ELF=circles

.PHONY: build, clean

build: $(ELF)

$(ELF): src/$(ELF).c
	$(CC) $(CFLAGS) $^ -o $@

run: $(ELF)
	./$<

clean:
	rm -f $(ELF)
