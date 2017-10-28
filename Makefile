NAME=parser
TESTSCANNER=scanner-test

CC=gcc
CFLAGS=-std=c99 -Wall -pedantic -g 

$(NAME): $(NAME).c
				$(CC) $(CFLAGS) $(NAME).c -o $(NAME)

$(TESTSCANNER): $(TESTSCANNER).c
				$(CC) $(CFLAGS) $(TESTSCANNER).c -o $(TESTSCANNER)

all:
	$(CC) $(CFLAGS) $(NAME) -o NAME
clean:
	rm -f *.o *.core parser scanner-test
scanner:
	$(CC) $(CFLAGS) $(TESTSCANNER) -o TESTSCANNER