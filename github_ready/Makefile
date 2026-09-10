# Bank Management System - Makefile
#
# Usage:
#   make          -> build the executable (./bin/bank_system)
#   make run      -> build (if needed) and run it
#   make clean    -> remove all build artifacts

# Override on the command line if needed, e.g.: make CXX=g++-16
CXX      ?= g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Iinclude
BIN_DIR  := bin
OBJ_DIR  := obj
TARGET   := $(BIN_DIR)/bank_system

SOURCES  := $(wildcard src/*.cpp)
OBJECTS  := $(patsubst src/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS)

$(OBJ_DIR)/%.o: src/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
