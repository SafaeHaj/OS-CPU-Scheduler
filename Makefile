# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -Iinclude -std=c++17

# Directories
SRC_DIR = src
CORE_DIR = $(SRC_DIR)/core
BUILD_DIR = build
BUILD_CORE_DIR = $(BUILD_DIR)/core
BIN_DIR = bin

# Source files
MAIN_SRC = $(SRC_DIR)/main.cpp
CORE_SRCS = $(wildcard $(CORE_DIR)/*.cpp)
OTHER_SRCS = $(filter-out $(MAIN_SRC),$(wildcard $(SRC_DIR)/*.cpp))

# Object files
MAIN_OBJ = $(BUILD_DIR)/main.o
CORE_OBJS = $(patsubst $(CORE_DIR)/%.cpp,$(BUILD_CORE_DIR)/%.o,$(CORE_SRCS))
OTHER_OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(OTHER_SRCS))
ALL_OBJS = $(MAIN_OBJ) $(CORE_OBJS) $(OTHER_OBJS)

# Executable name
EXEC = $(BIN_DIR)/scheduler

# Default target
all: $(EXEC)

# Linking
$(EXEC): $(ALL_OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compilation rules
$(MAIN_OBJ): $(MAIN_SRC) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_CORE_DIR)/%.o: $(CORE_DIR)/%.cpp | $(BUILD_CORE_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Ensure output directories exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_CORE_DIR): | $(BUILD_DIR)
	mkdir -p $(BUILD_CORE_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Clean
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

# Debug - print variables
debug:
	@echo "MAIN_SRC: $(MAIN_SRC)"
	@echo "CORE_SRCS: $(CORE_SRCS)"
	@echo "OTHER_SRCS: $(OTHER_SRCS)"
	@echo "MAIN_OBJ: $(MAIN_OBJ)"
	@echo "CORE_OBJS: $(CORE_OBJS)"
	@echo "OTHER_OBJS: $(OTHER_OBJS)"
	@echo "ALL_OBJS: $(ALL_OBJS)"

.PHONY: all clean debug
