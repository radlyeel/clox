PROG = clox

CC = clang
CFLAGS =  -Wall

OBJS = chunk.o\
	   main.o\
	   memory.o\
	   debug.o\
	   value.o\
	   vm.o\
	   compiler.o\
	   scanner.o

clox: $(OBJS)
	$(CC) $(OBJS) -o $(PROG)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(PROG)$(OBJS) 

check: $(PROG)
	./$(PROG)

