NAME=parser
TESTS=tests
TESTSCANNER=scanner-test

CC=gcc
CFLAGS=-std=c99 -Wall -pedantic -g 

$(NAME): $(NAME).c
				$(CC) $(CFLAGS) $(NAME).c -o $(NAME)

$(TESTS): $(TESTSCANNER).c
		  $(CC) $(CFLAGS) $(TESTSCANNER).c -o $(TESTSCANNER)
		  bash test-scanner.sh

all:
	$(CC) $(CFLAGS) $(NAME) -o NAME
	$(CC) $(CFLAGS) $(TESTSCANNER) -o TESTSCANNER
clean:
	rm -f *.o *.core parser scanner-test Testy/*.o Testy/*.err *.txt

