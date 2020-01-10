PROG = grpwk
SRCS = input_win.c linked_list.c submit/grpwk.c submit/itoi.c submit/sunday.c
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