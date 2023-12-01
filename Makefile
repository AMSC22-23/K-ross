# Makefile for C++ project with source files in a separate directory


# Makefile location: has to be in the root of the project

# Compiler
CXX = g++ 

# Compiler flags
# -std=c++20 specifies the C++ standard
# -g adds debugging information to the executable file
# -Wall turns on most, but not all, compiler warnings
# -Wextra enables some extra warning flags that are not enabled by -Wall
# -Wpedantic to request all the warnings demanded by strict ISO C and ISO C++
# -Wunused warns about unused variables.
# -Wuninitialized warns about uninitialized variables.
# -Wshadow warns about variable shadowing.
# -Wconversion warns about implicit type conversions.
CXXFLAGS = -std=c++20 -I/usr/include/boost/

# Build directory in the root
BUILD_DIR = ./build

# Source directory, in the root, contains all sourcefiles (.cpp)
SRC_DIR = ./src

# Executable name
TARGET = exe

# Find all source files in the source directory
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Object files
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# Default target
all: $(TARGET)

# Rule to link the program
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to compile source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to clean the build directory
clean:
	rm -f $(BUILD_DIR)/*.o $(TARGET)

# 
.PHONY: all clean