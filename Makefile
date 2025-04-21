# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Iinclude

# Directories
INCLUDE_DIR = include
SRC_DIR = src
BIN_DIR = bin

# Search paths for header and source files
vpath %.h $(INCLUDE_DIR)
vpath %.cpp $(SRC_DIR)

# Source files and object files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BIN_DIR)/%.o)


# Clean up
clean:
	rm -rf $(BIN_DIR)

.PHONY: all clean