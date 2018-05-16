NAME = ftf

CC ?= gcc
LIBS = -lfontconfig -lXft
CFLAGS += -std=c99 -pedantic -Wall
CFLAGS += $(shell freetype-config --cflags)

PREFIX ?= /usr/local
BINPREFIX = $(PREFIX)/bin
MANPREFIX = $(PREFIX)/man

BIN = $(NAME)
SRC = $(NAME).c
MAN = $(NAME).1

$(BIN): $(SRC)
	$(CC) $< -o $@ $(CFLAGS) $(LIBS)

install:
	mkdir -p $(DESTDIR)$(BINPREFIX)/
	cp -f $(BIN) $(DESTDIR)$(BINPREFIX)/
	mkdir -p $(DESTDIR)$(MANPREFIX)/man1/
	cp -r $(MAN) $(DESTDIR)$(MANPREFIX)/man1/$(MAN)

uninstall:
	rm -f $(DESTDIR)$(BINPREFIX)/$(BIN)
	rm -f $(DESTDIR)$(MANPREFIX)/man1/$(MAN)

clean:
	rm -f $(BIN)

.PHONY: install uninstall clean
