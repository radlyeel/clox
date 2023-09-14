# Makefile for challenges

PROG = demo
OBJS = main.o DLList.o
ARGS =

CC =  gcc
CFLAGS = -Wall -Werror

# Below here should not change
$(PROG): $(OBJS)
	$(CC) $(OBJS) -o $(PROG)

check: $(PROG)
	./$(PROG) $(ARGS)

clean:
	rm -f $(PROG) $(OBJS)

