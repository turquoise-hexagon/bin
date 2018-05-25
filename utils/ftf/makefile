NAME = ftf

CC ?= gcc
LIBS = -lfontconfig -lXft
CFLAGS += -std=c99 -pedantic -Wall
CFLAGS += $(shell freetype-config --cflags)

PREFIX ?= /usr/local
BINPREFIX = $(PREFIX)/bin

BIN = $(NAME)
SRC = $(NAME).c

$(BIN): $(SRC)
	$(CC) $< -o $@ $(CFLAGS) $(LIBS)

install:
	mkdir -p $(DESTDIR)$(BINPREFIX)/
	cp -f $(BIN) $(DESTDIR)$(BINPREFIX)/

uninstall:
	rm -f $(DESTDIR)$(BINPREFIX)/$(BIN)

clean:
	rm -f $(BIN)

.PHONY: install uninstall clean
