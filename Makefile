# Compiler
CC = gcc

# Directories
INCLUDE_DIR = ./include
SRC_DIR = ./src

# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)

# Object files
OBJ_FILES = $(SRC_FILES:.c=.o)

# Base output executable name
BASE_OUTPUT = rubik_solver

# Platform-specific settings
ifeq ($(OS),Windows_NT)
	LIB_DIR = ./lib_win
	LIBS = -lglfw3 -lgdi32 -lopengl32 -lglu32 -lcomdlg32 -mwindows
	CFLAGS = -I$(INCLUDE_DIR)
	LDFLAGS = -L$(LIB_DIR)
	RM = cmd /C del /Q /F
	CONVERT_PATH = $(subst /,\,$1)
	OUTPUT = $(BASE_OUTPUT).exe
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		LIB_DIR = ./lib_linux
		LIBS = -lGL -lglfw3 -lm
		CFLAGS = -I$(INCLUDE_DIR)
		LDFLAGS = -L$(LIB_DIR)
		RM = rm -f
		PREBUILD = sudo ln -sf /usr/lib/x86_64-linux-gnu/libGL.so.1 /usr/lib/libGL.so
		OUTPUT = $(BASE_OUTPUT)
	endif
	ifeq ($(UNAME_S),Darwin)
		CC = gcc-14
		LIB_DIR = ./lib_macos
		LIBS = -lglfw -framework OpenGL
		CFLAGS = -I$(INCLUDE_DIR)
		LDFLAGS = -L$(LIB_DIR)
		RM = rm -f
		OUTPUT = $(BASE_OUTPUT)
	endif
endif

# Default target
all: $(OUTPUT) clean_obj

# Build target (linking stage)
$(OUTPUT): $(OBJ_FILES)
	$(PREBUILD)
	$(CC) -o $(OUTPUT) $(OBJ_FILES) $(LDFLAGS) $(LIBS)

# Rule to compile object files (compilation stage)
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $< -o $@ $(CFLAGS) -Ofast -Wno-stringop-overflow -Wno-unused-result -Wno-unknown-warning-option

# Clean object files
clean_obj:
ifeq ($(OS),Windows_NT)
	-$(RM) $(call CONVERT_PATH,$(OBJ_FILES)) > nul 2>&1
else
	-$(RM) $(OBJ_FILES)
endif

clean:
ifeq ($(OS),Windows_NT)
	-$(RM) $(call CONVERT_PATH,$(OBJ_FILES)) $(call CONVERT_PATH,$(OUTPUT)) > nul 2>&1
else
	-$(RM) $(OBJ_FILES) $(OUTPUT)
endif
