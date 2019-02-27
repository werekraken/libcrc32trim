CC = gcc
CFLAGS = -Wall -Wcast-align -Wcast-qual -Wimplicit -Wpointer-arith -Wredundant-decls -Wreturn-type -Wshadow

ifndef PREFIX
PREFIX = /usr/local
endif

ifndef INCLUDEDIR
INCLUDEDIR = $(PREFIX)/include
endif

ifndef LIBDIR
LIBDIR = $(PREFIX)/lib
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
	mkdir -p $(DESTDIR)$(LIBDIR)
	mkdir -p $(DESTDIR)$(INCLUDEDIR)
	install $(SHAREDLIBV) $(DESTDIR)$(LIBDIR)/
	ln -s $(SHAREDLIBV) $(DESTDIR)$(LIBDIR)/$(SHAREDLIB)
	ln -s $(SHAREDLIBV) $(DESTDIR)$(LIBDIR)/$(SHAREDLIBM)
	cp crc32trim.h $(DESTDIR)$(INCLUDEDIR)/

.PHONY: uninstall
uninstall:
	rm $(DESTDIR)$(LIBDIR)/$(SHAREDLIB)
	rm $(DESTDIR)$(LIBDIR)/$(SHAREDLIBM)
	rm $(DESTDIR)$(LIBDIR)/$(SHAREDLIBV)
	rm $(DESTDIR)$(INCLUDEDIR)/crc32trim.h
