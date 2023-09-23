PROG = clox

CC = clang
CFLAGS =  -Wall -Werror

OBJS = main.o

clox: main.o
	$(CC) main.o -o clox

%.o: %.c
main.o: main.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $((PROG) $(OBJS)

check: $(PROG)
	./$(PROG)

