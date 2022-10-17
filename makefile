CC=gcc
CFLAGS=-I .
DEPS = main.h io.h
OBJ = main.c io.c

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)