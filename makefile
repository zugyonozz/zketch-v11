# Compiler
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++20 -Iincludes
LDFLAGS := -lgdi32 -lgdiplus

# Directories
SRC_DIR := src
IMPL_DIR := includes/impl
BIN_DIR := bin

# Output binary
TARGET := $(BIN_DIR)/temp.exe

# Source files
SRC_FILES := $(SRC_DIR)/temp.cpp \
             $(IMPL_DIR)/zbitmap_impl.cpp \
             $(IMPL_DIR)/zdrawer_impl.cpp \
             $(IMPL_DIR)/zevent_impl.cpp \
             $(IMPL_DIR)/zunit_impl.cpp

# Object files
OBJ_FILES := $(SRC_FILES:.cpp=.o)

# Default target
all: $(TARGET)

# Link
$(TARGET): $(OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJ_FILES) -o $@ $(LDFLAGS)

# Compile
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJ_FILES) $(TARGET)

# Run program
run: $(TARGET)
	./$(TARGET)
