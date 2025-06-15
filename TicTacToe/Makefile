CXX = g++
CXXFLAGS = -std=c++17 -Wall -g

SFML_PATH = /opt/homebrew
SFML_INCLUDE = -I$(SFML_PATH)/include
SFML_LIBS_PATH = -L$(SFML_PATH)/lib
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Project files and directories
SRCS = main.cpp game.cpp ai.cpp
BIN_DIR = bin

# Create a list of object files (.o) based on the source files
OBJS = $(addprefix $(BIN_DIR)/,$(SRCS:.cpp=.o))
TARGET = $(BIN_DIR)/TicTacToe

# Default rule
all: $(BIN_DIR) $(TARGET)

# Rule to create the binary directory if it doesn't exist
$(BIN_DIR):
	@mkdir -p $(BIN_DIR)
	@echo "Created directory $(BIN_DIR)/"

# Rule to link the final executable
$(TARGET): $(OBJS)
	@echo "Linking..."
	$(CXX) $(OBJS) -o $(TARGET) $(SFML_LIBS_PATH) $(SFML_LIBS)
	@echo "Build finished: $(TARGET)"

# Rule to compile a .cpp file into a .o object file within the bin directory
$(BIN_DIR)/%.o: %.cpp
	@echo "Compiling $< to $@..."
	$(CXX) $(CXXFLAGS) $(SFML_INCLUDE) -c $< -o $@

# "Phony" target to clean up build files.
.PHONY: clean all

clean:
	@echo "Cleaning up..."
	rm -rf $(BIN_DIR)
