# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Iinclude -Iexternal/wsServer/include

# Directory containing wsServer library
LIB_DIR = ./external/wsServer

# Name of the wsServer library
LIB_NAME = ws

# Source files directory
SRC_DIR = ./src

# Object file directory
OBJ_DIR = ./build

# Source files
SRC := $(wildcard $(SRC_DIR)/*.c)

# Object files
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Executable name
EXE = server

# Build directory
BUILD_DIR = build

# Targets
all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $(EXE) -L$(LIB_DIR) -l$(LIB_NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(EXE)

