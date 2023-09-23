PROG = clox

CC = clang
CFLAGS =  -Wall -Werror

OBJS = chunk.o main.o memory.o debug.o

clox: $(OBJS)
	$(CC) $(OBJS) -o $(PROG)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(PROG) $(OBJS)

check: $(PROG)
	./$(PROG)

