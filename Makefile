# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -std=c11

# Source files
SRC = maze_generator.c file_manager.c main.c

# Output executable
OUT = maze

# Build the project
all: $(OUT)

# Link the object files to create the executable
$(OUT): $(SRC)
	$(CC) $(CFLAGS) -o $(OUT) $(SRC)

# Clean up the generated files
clean:
	rm -f $(OUT)

# Phony targets
.PHONY: all clean
