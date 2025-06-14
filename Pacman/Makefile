COMPILER := g++
OUTPUT_DIR := bin
SFML_INCLUDE_DIR := /opt/homebrew/include
SFML_LIB_DIR := /opt/homebrew/lib
SFML_LIBS := -lsfml-graphics -lsfml-window -lsfml-system
CXXFLAGS := -std=c++17 -stdlib=libc++ -Wall -g -I$(SFML_INCLUDE_DIR)
LDFLAGS := -stdlib=libc++ -L$(SFML_LIB_DIR) $(SFML_LIBS)

# Get all .cpp files in the current directory
SOURCES := $(wildcard *.cpp)

# Derive object file names from source file names
OBJECTS := $(patsubst %.cpp,$(OUTPUT_DIR)/%.o,$(SOURCES))

# The executable name
TARGET := $(OUTPUT_DIR)/Pacman

# Default rule to build the executable
all: $(TARGET)

# Rule to link the object files into the executable
$(TARGET): $(OBJECTS)
	@mkdir -p $(OUTPUT_DIR)
	$(COMPILER) $(LDFLAGS) -o $@ $^

# Rule to compile each .cpp file into a .o file
$(OUTPUT_DIR)/%.o: %.cpp Constants.h
	@mkdir -p $(OUTPUT_DIR)
	$(COMPILER) $(CXXFLAGS) -c $< -o $@

# Rule to clean the build directory
clean:
	rm -rf $(OUTPUT_DIR)

.PHONY: all clean