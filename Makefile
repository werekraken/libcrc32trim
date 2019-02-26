CC = gcc
CFLAGS = -Wall -Wcast-align -Wcast-qual -Wimplicit -Wpointer-arith -Wredundant-decls -Wreturn-type -Wshadow
ifndef PREFIX
PREFIX = /usr/local
endif

include VERSION

SHAREDLIB=libcrc32trim.so
SHAREDLIBV=libcrc32trim.so.$(LIBCRC32TRIM_VERSION)
SHAREDLIBM=libcrc32trim.so.$(firstword $(subst ., ,$(LIBCRC32TRIM_VERSION)))

all: $(SHAREDLIBV)

%.o: %.c
	$(CC) $(CFLAGS) -fpic -c -o $@ $<

$(SHAREDLIBV): crc32trim.o
	$(CC) -shared -o $(SHAREDLIBV) crc32trim.o -lz

.PHONY: clean
clean:
	rm -f crc32trim.o $(SHAREDLIBV)

.PHONY: install
install: $(SHAREDLIBV)
	mkdir -p $(DESTDIR)$(PREFIX)/lib
	mkdir -p $(DESTDIR)$(PREFIX)/include
	install $(SHAREDLIBV) $(DESTDIR)$(PREFIX)/lib/
	ln -s $(SHAREDLIBV) $(DESTDIR)$(PREFIX)/lib/$(SHAREDLIB)
	ln -s $(SHAREDLIBV) $(DESTDIR)$(PREFIX)/lib/$(SHAREDLIBM)
	cp crc32trim.h $(DESTDIR)$(PREFIX)/include/

.PHONY: uninstall
uninstall:
	rm $(DESTDIR)$(PREFIX)/lib/$(SHAREDLIB)
	rm $(DESTDIR)$(PREFIX)/lib/$(SHAREDLIBM)
	rm $(DESTDIR)$(PREFIX)/lib/$(SHAREDLIBV)
	rm $(DESTDIR)$(PREFIX)/include/crc32trim.h
