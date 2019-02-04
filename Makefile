CC = gcc
CFLAGS = -Wall -Wcast-align -Wcast-qual -Wimplicit -Wpointer-arith -Wredundant-decls -Wreturn-type -Wshadow
PREFIX = /usr/local

all: libcrc32trim.so

%.o: %.c
	$(CC) $(CFLAGS) -fpic -c -o $@ $<

libcrc32trim.so: crc32trim.o
	$(CC) -shared -o libcrc32trim.so crc32trim.o

.PHONY: clean
clean:
	rm -f crc32trim.o libcrc32trim.so

.PHONY: install
install: libcrc32trim.so
	mkdir -p $(DESTDIR)$(PREFIX)/lib
	mkdir -p $(DESTDIR)$(PREFIX)/include
	install $^ $(DESTDIR)$(PREFIX)/lib/
	cp crc32trim.h $(DESTDIR)$(PREFIX)/include/

.PHONY: uninstall
uninstall:
	rm $(DESTDIR)$(PREFIX)/lib/libcrc32trim.so
	rm $(DESTDIR)$(PREFIX)/include/crc32trim.h
