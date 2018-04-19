NAME = ftw

CC = gcc
LIBS = -lfreetype
CFLAGS += -std=c99 -pedantic -Wall
CFLAGS += $(shell freetype-config --cflags)

PREFIX = /usr/local
BINPREFIX = $(PREFIX)/bin

BIN = $(NAME)
SRC = $(NAME).c

$(BIN): $(SRC)
	$(CC) $< -o $@ $(CFLAGS) $(LIBS)

install:
	mkdir -p "$(DESDIR)$(BINPREFIX)"
	cp -f "$(BIN)" "$(DESTDIR)$(BINPREFIX)"

uninstall:
	rm -f "$(DESTDIR)$(BINPREFIX)/$(NAME)"

clean:
	rm -f $(BIN)

.PHONY: install uninstall clean
