PROG = grpwk
CC = gcc
CFLAGS = -W -Wall -Wextra -Wconversion -Wshadow

FILES = $(shell gcc test_distance.c -o distance | find ./ \( -name "*.c" \) \( -not -name "*test*" \))
default:
	$(CC) $(CFLAGS) -o $(PROG) $(FILES)