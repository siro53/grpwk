PROG = grpwk
CC = gcc
CFLAGS = -W -Wall -Wextra -Wconversion -Wshadow

FILES = $(shell find ./ \( -name "*.c" \) -not -name "*test*")
default:
	$(CC) $(CFLAGS) -o $(PROG) $(FILES)
