CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude
LDFLAGS = 

SRC_DIR = src
OBJ_DIR = build

# Find all .cpp files not in gui directories
SRCS := $(shell find $(SRC_DIR) -type f -name '*.cpp' ! -path "*/gui/*")
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

TARGET = bin/cpu_scheduler_cli

$(TARGET): $(OBJS)
	@mkdir -p $(dir $@)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR) $(TARGET)
