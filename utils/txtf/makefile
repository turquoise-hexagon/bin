NAME=txtf

CC ?= gcc

LIBS = -lfreetype -lfontconfig -lXft
CFLAGS += -std=c99 -pedantic -Wall
CFLAGS += $(shell freetype-config --cflags)

PREFIX ?= /usr/local
BINPREFIX = $(PREFIX)/bin

BIN = $(NAME)
SRC = $(NAME).c

$(BIN): $(SRC)
	$(CC) $< -o $@ $(CFLAGS) $(LIBS)

install:
	mkdir -p $(DESTDIR)$(BINPREFIX)
	cp -r $(BIN) $(DESTDIR)$(BINPREFIX)/

uninstall:
	rm -f $(DESTDIR)$(BINPREFIX)

clean:
	rm -f $(BIN)

.PHONY: install uninstall clean
