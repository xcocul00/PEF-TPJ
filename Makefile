NAME=parser
CC=gcc
CFLAGS=-std=c99 -Wall -pedantic -g 

$(NAME): $(NAME).c
				$(CC) $(CFLAGS) $(NAME).c -o $(NAME)

all:
	$(CC) $(CFLAGS) $(NAME) -o NAME
clean:
	rm -f *.o *.core parser