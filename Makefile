CC = gcc
CFLAGS = -std=c23 -Wall -Iinclude
LDFLAGS = -Llib -lvector  # Optional: if you're linking an actual libvector.a

SRC := $(wildcard src/*.c)
OBJDIR := build
OBJ := $(patsubst src/%.c, $(OBJDIR)/%.o, $(SRC))
BIN := $(OBJDIR)/main

all: $(BIN)

$(BIN): $(OBJ)
	@mkdir -p $(OBJDIR)
	$(CC) $(OBJ) -o $(BIN) $(LDFLAGS)

$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)
