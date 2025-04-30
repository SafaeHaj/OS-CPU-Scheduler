# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Iinclude -Isrc/gui

# Directories
SRC_DIR = src
GUI_DIR = src/gui
BUILD_DIR = build
BIN_DIR = bin

# Source files
SRCS = main.cpp $(GUI_DIR)/ProcessUIManager.cpp $(GUI_DIR)/ProcessUI.cpp $(GUI_DIR)/DropDownMenu.cpp
OBJS = $(SRCS:.cpp=.o)
OBJ_PATHS = $(patsubst %.o,$(BUILD_DIR)/%.o,$(notdir $(OBJS)))

# Executable name
TARGET = $(BIN_DIR)/main

# Default target
all: $(TARGET)

# Linking
$(TARGET): $(OBJ_PATHS) | $(BIN_DIR)
	$(CXX) $^ -o $@ -lsfml-graphics -lsfml-window -lsfml-system

# Compilation
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(GUI_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Ensure output directories exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Clean
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: all clean
