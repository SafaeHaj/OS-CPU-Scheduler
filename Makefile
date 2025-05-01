# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Iinclude -Isrc/gui

# Directories
SRC_DIR = src
CORE_DIR = src/core
GUI_DIR = src/gui
BUILD_DIR = build
BIN_DIR = bin
CORE_BIN_DIR = $(BIN_DIR)/core
GUI_BIN_DIR = $(BIN_DIR)/gui

# Source files
SRCS = main.cpp $(wildcard $(GUI_DIR)/*.cpp) $(wildcard $(CORE_DIR)/*.cpp)
OBJS = $(SRCS:.cpp=.o)
OBJ_PATHS = $(patsubst %.o,$(BUILD_DIR)/%.o,$(notdir $(OBJS)))

# Executable name
TARGET = $(GUI_BIN_DIR)/main
EXEC = $(CORE_BIN_DIR)/scheduler

# Default target
all: $(TARGET) 

# Linking
$(TARGET): $(OBJ_PATHS) | $(GUI_BIN_DIR)
	$(CXX) $^ -o $@ -lsfml-graphics -lsfml-window -lsfml-system

# Compilation
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(GUI_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# $(EXEC): $(OBJ)
# 	$(CXX) $(CXXFLAGS) $^ -o $@

# Ensure output directories exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(CORE_BIN_DIR):
	mkdir -p $(CORE_BIN_DIR)

$(GUI_BIN_DIR):
	mkdir -p $(GUI_BIN_DIR)

# Clean
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: all clean
