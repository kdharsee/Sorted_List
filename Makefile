CC=gcc
CFLAGS=-Wall -g -c -o
MAINFLAGS=-Wall -g -o
all:
	$(CC) $(CFLAGS) sorted-list.o sorted-list.c
	$(CC) $(MAINFLAGS) main main.c	
main:
	$(CC) $(MAINFLAGS) main main.c
sorted-list:
	$(CC) $(CFLAGS) sorted-list.o sorted-list.c
clean:
	rm -rf sorted-list main
	rm -rf *.o
