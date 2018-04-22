NAME = fts

CC ?= gcc
LIBS = -lfreetype
CFLAGS += -std=c99 -pedantic -Wall
CFLAGS += $(shell freetype-config --cflags)

PREFIX ?= /usr/local
BINPREFIX = $(PREFIX)/bin
MANPREFIX = $(PREFIX)/man

BIN = $(NAME)
SRC = $(NAME).c

$(BIN): $(SRC)
	$(CC) $< -o $@ $(CFLAGS) $(LIBS)

install:
	mkdir -p $(DESTDIR)$(BINPREFIX)/
	cp -f $(BIN) $(DESTDIR)$(BINPREFIX)/
	mkdir -p $(DESTDIR)$(MANPREFIX)/man1/
	cp -f $(NAME).1 $(DESTDIR)$(MANPREFIX)/man1/

uninstall:
	rm -f $(DESTDIR)$(BINPREFIX)/$(BIN)
	rm -f $(DESTDIR)$(MANPREFIX)/man1/$(NAME).1

clean:
	rm -f $(BIN)

.PHONY: install uninstall clean
