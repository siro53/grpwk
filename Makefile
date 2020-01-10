PROG = grpwk
SRCS = input_win.c ahocorasick.c ahotrie.c constructions.c linked_list.c queue.c itoi/BM+.c itoi/grpwk.c itoi/itoi.c
CC = gcc
CFLAGS = -W -Wall -Wextra -Wconversion -Wshadow
LDFLAGS = 
OBJS = $(SRCS:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@
$(PROG): $(OBJS)
	$(CC) $(LDFLAGS) -o $(PROG) $^
clean:
	rm  $(OBJS) $(PROG)