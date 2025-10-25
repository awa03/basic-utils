# Project name and directories
PROJECT_NAME = basic-utils
SRC_DIR = src
INC_DIR = include
BIN_DIR = bin

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -I$(INC_DIR) -Wall -Wextra -O2

# Collect all .cpp files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BIN_DIR)/%.o)

# Output executable
TARGET = $(BIN_DIR)/$(PROJECT_NAME)

# Default rule
all: $(BIN_DIR) $(TARGET)

# Link object files into executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile .cpp files into .o
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create bin directory if not exists
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Clean build artifacts
clean:
	rm -rf $(BIN_DIR)/*.o $(TARGET)

# Convenience rule for rebuild
rebuild: clean all

.PHONY: all clean rebuild

