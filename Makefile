CC = gcc
CFLAGS = -std=c99 -pedantic -Wall
RM = rm -f

NAME = bf93


.PHONY: all clean

all: $(NAME) clean

bf93.o: src/bf93.c
	$(CC) -c $(CFLAGS) -o $@ $<

ops.o: src/ops.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(NAME): bf93.o ops.o
	$(CC) $(CFLAGS) -o $@ $+

clean:
	$(RM) ops.o bf93.o
