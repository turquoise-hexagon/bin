NAME=txtf

CC ?= gcc

LIBS = -lfreetype -lfontconfig -lXft
CFLAGS += -std=c99 -pedantic -Wall
CFLAGS += $(shell freetype-config --cflags)

BIN = $(NAME)
SRC = $(NAME).c

$(BIN): $(SRC)
	$(CC) $< -o $@ $(CFLAGS) $(LIBS)

clean:
	rm -f $(BIN)

.PHONY: clean
