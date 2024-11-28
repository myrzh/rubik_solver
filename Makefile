# Compiler
CC = gcc

# Directories
INCLUDE_DIR = ./include
SRC_DIR = ./src

# Source files
SRC_FILES = $(SRC_DIR)/rubik_solver.c $(SRC_DIR)/glad.c $(SRC_DIR)/sfd.c $(SRC_DIR)/draw.c $(SRC_DIR)/window.c $(SRC_DIR)/algo.c $(SRC_DIR)/colors.c $(SRC_DIR)/cube.c $(SRC_DIR)/interface.c $(SRC_DIR)/objects.c $(SRC_DIR)/shaders.c

# Output executable
OUTPUT = rubik_solver

# Platform-specific settings
ifeq ($(OS),Windows_NT)
	LIB_DIR = ./lib_win
	LIBS = -lglfw3 -lgdi32 -lopengl32 -lglu32 -lcomdlg32 -mwindows
	CFLAGS = -I$(INCLUDE_DIR) -L$(LIB_DIR)
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		LIB_DIR = ./lib_linux
		LIBS = -lGL -lglfw3 -lm
		CFLAGS = -I$(INCLUDE_DIR) -L$(LIB_DIR)
		PREBUILD = sudo ln -sf /usr/lib/x86_64-linux-gnu/libGL.so.1 /usr/lib/libGL.so
	endif
	ifeq ($(UNAME_S),Darwin)
		LIB_DIR = ./lib_macos
		LIBS = -lglfw -framework OpenGL
		CFLAGS = -I$(INCLUDE_DIR) -L$(LIB_DIR)
	endif
endif

# Build target
$(OUTPUT):
	$(PREBUILD)
	$(CC) -o $(OUTPUT) $(SRC_FILES) $(CFLAGS) $(LIBS)

# Clean target
clean:
	rm -f $(OUTPUT)
