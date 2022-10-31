CC=gcc
CFLAGS=-I .
DEPS = comp.h instr.h io.h main.h 
OBJ = comp.c instr.c io.c main.c 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)