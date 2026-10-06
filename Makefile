CC = gcc

CFLAGS = -O2 -Wall -fPIC

all: enlib.so example

enlib.so: enlib.o
	$(CC) enlib.o -shared -o enlib.so

enlib.o: enlib.c enlib.h
	$(CC) -c $(CFLAGS) enlib.c

example: example.o enlib.so
	$(CC) example.o ./enlib.so -Wl,-rpath,'$$ORIGIN' -o example

example.o: example.c enlib.h
	$(CC) -c $(CFLAGS) example.c

clean:
	rm -f *.o *.so example