PROG = grpwk
OBJS = test_ahocorasick.o ahocorasick.o ahotrie.o ahotext.o queue.o
CC = gcc
# CFLAGS = -W -Wall -Wextra -Wconversion -Wshadow
CFLAGS = 
LDFLAGS = 

.SUFFIXES: .c

$(PROG): $(OBJS)
	$(CC) $(LDFLAGS) -o $(PROG) $^
.c.o:
	$(CC) $(CFLAGS) -c $<
clean:
	rm  $(OBJS) $(PROG)
