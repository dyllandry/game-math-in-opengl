# Makefile implementation learned from <https://stackoverflow.com/a/52036564/7933478>
CC=gcc

# Source files are anything that ends with .c
SOURCES := $(wildcard src/*.c)
# Object files are all .o versions of the .c files
OBJECTS := $(patsubst %.c,%.o,$(SOURCES))

# Say that each .c file depends on a .d file.
# (Later, the -MMD flag generates a .d file for each .c file. The .d file is a
# makefile containing rules for compiling the .c file along with any non-system
# headers it includes. This is all a way of automatically making makefile rules
# that each .c file depends on any header it includes, and should be recompiled
# if any of the headers change.)
DEPENDS := $(patsubst %.c,%.d,$(SOURCES))

# Rule for compiling main executable
main: $(OBJECTS)
	$(CC) $^ -o bin/$@ -lglfw -lGL -ldl -lm -fPIE

# Includes other make files in this make file (- means if it exists)
-include $(DEPENDS)

# Rule for compiling individual object files.
%.o: %.c makefile
	$(CC) -MMD -MP -c $< -o $@

