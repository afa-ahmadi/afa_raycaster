# Compiler
CC = gcc

# Flags
CFLAGS = -Wall -Wextra -std=c11 -Iinclude

# Raylib + Math
LIBS = $(shell pkg-config --cflags --libs raylib) -lm

# Files
SRC = $(wildcard src/*.c)
OUT = build/raycaster

# Default target
all: $(OUT)

# Build
$(OUT): $(SRC)
	$(CC) $(SRC) -o $(OUT) $(CFLAGS) $(LIBS)

# Run
run: all
	./$(OUT)

# Clean
clean:
	rm -f $(OUT)
