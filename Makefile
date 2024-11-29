# Compiler
CC = gcc

# Directories
INCLUDE_DIR = ./include
SRC_DIR = ./src

# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)

# Object files
OBJ_FILES = $(SRC_FILES:.c=.o)

# Output executable
OUTPUT = rubik_solver

# Platform-specific settings
ifeq ($(OS),Windows_NT)
	LIB_DIR = ./lib_win
	LIBS = -lglfw3 -lgdi32 -lopengl32 -lglu32 -lcomdlg32 -mwindows
	CFLAGS = -I$(INCLUDE_DIR)
	LDFLAGS = -L$(LIB_DIR)
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		LIB_DIR = ./lib_linux
		LIBS = -lGL -lglfw3 -lm
		CFLAGS = -I$(INCLUDE_DIR)
		LDFLAGS = -L$(LIB_DIR)
		PREBUILD = sudo ln -sf /usr/lib/x86_64-linux-gnu/libGL.so.1 /usr/lib/libGL.so
	endif
	ifeq ($(UNAME_S),Darwin)
		LIB_DIR = ./lib_macos
		LIBS = -lglfw -framework OpenGL
		CFLAGS = -I$(INCLUDE_DIR)
		LDFLAGS = -L$(LIB_DIR)
	endif
endif

# Default target
all: $(OUTPUT) clean_objs

# Build target (linking stage)
$(OUTPUT): $(OBJ_FILES)
	$(PREBUILD)
	$(CC) -o $(OUTPUT) $(OBJ_FILES) $(LDFLAGS) $(LIBS)

# Rule to compile object files (compilation stage)
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

# Rule to clean up object files
clean_objs:
	rm -f $(OBJ_FILES)

# Clean target
clean:
	rm -f $(OBJ_FILES) $(OUTPUT)
