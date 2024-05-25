PROG = clox
SRC =
OBJS  = main.o

CC = gcc
CFLAGS  = -std=c99 -Wall -Werror

$(PROG): $(OBJS)
	$(CC) $(OBJS) -o $(PROG)

clean:
	rm -rf $(PROG) $(OBJS)

check: $(PROG)
	./$(PROG) $(SRC)
