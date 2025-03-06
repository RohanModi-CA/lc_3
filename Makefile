# Compiler
CC = gcc

# Executable name
EXECUTABLE = mygame

# Directories
RAYLIB_DIR = resources/lib/raylib
MESH_DIR = resources/mesh
WORLD_FUNCS_DIR = resources/world_funcs
FAST_OBJ_DIR = resources/mesh/lib

# Source files (explicitly listed - best practice)
SOURCES = main.c \
          $(MESH_DIR)/mesh_load.c \
          $(MESH_DIR)/mesh_triangularize.c \
          $(MESH_DIR)/mesh_texture.c \
          $(MESH_DIR)/mesh_move.c \
          $(FAST_OBJ_DIR)/fast_obj.c \
		  $(WORLD_FUNCS_DIR)/debug_f3.c

# Object files (automatically generated from SOURCES)
OBJECTS = $(SOURCES:.c=.o)

# --- Compilation Flags ---
# Common flags for all compilations
COMMON_CFLAGS = -Wall -g 

# Include directories (use variables for clarity)
INCLUDES = -I$(RAYLIB_DIR) -I$(MESH_DIR) -I$(WORLD_FUNCS_DIR) -I$(FAST_OBJ_DIR)

# CFLAGS for the entire project (combining common flags and includes)
CFLAGS = $(COMMON_CFLAGS) $(INCLUDES)

# --- Linking ---
# Library directories
LDFLAGS = -L$(RAYLIB_DIR)

# Libraries to link
LIBS = -lraylib -lm

# --- Rules ---

# Default target: Build the executable
all: $(EXECUTABLE)

# Rule to link the executable
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(EXECUTABLE) $(OBJECTS) $(LIBS)

# Rule to compile individual source files into object files
#  This is the key part that was improved.
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# --- Dependencies (Important!) ---
# This section tells Make what each .o file depends on.  This is
# *critical* for correct incremental builds (only recompiling what's changed).
# We'll use the compiler to generate these automatically.

# Rule to generate dependencies
depend: $(SOURCES)
	$(CC) $(CFLAGS) -MM $(SOURCES) > .depend

# Include the generated dependencies
-include .depend

# --- Clean ---
# Rule to clean up the build
clean:
	rm -f $(OBJECTS) $(EXECUTABLE) .depend

# Phony targets (targets that aren't actual files)
.PHONY: all clean depend
