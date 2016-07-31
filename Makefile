all: libcrc32trim.so

libcrc32trim.so: crc32trim.o
	gcc -shared -o libcrc32trim.so crc32trim.o

crc32trim.o:
	gcc -c -Wall -Werror -fpic crc32trim.c

clean:
	rm -f crc32trim.o libcrc32trim.so
