CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++20 -Iincludes
LDFLAGS := -lgdi32 -lgdiplus

SRC_DIR := src
IMPL_DIR := includes/impl
OBJ_DIR := obj
BIN_DIR := bin

TARGET := $(BIN_DIR)/main.exe

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(IMPL_DIR)/*.cpp)

OBJ_FILES := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(notdir $(SRC_FILES)))

# Default target
all: $(TARGET)

# Link
$(TARGET): $(OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJ_FILES) -o $@ $(LDFLAGS)

# Compile rule
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(IMPL_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Run program
run: $(TARGET)
	./$(TARGET)