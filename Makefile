# Makefile for compiling main.cpp and tablero.cpp

# Compiler
CXX = g++ #x86_64-w64-mingw32-g++#g++

# Compiler flags
CXXFLAGS = -Wall -g -I./include #-m32

# Target executable
TARGET = main

# Build directory
BUILD_DIR = build

# Source files
SRCS = $(wildcard src/*.cpp) #main.cpp tablero.cpp

# Object files
OBJS = $(SRCS:src/%.cpp=$(BUILD_DIR)/%.o) #$(SRCS:.cpp=.o)

# Create build directory
EXEC = $(BUILD_DIR)/$(TARGET)

# Determine the OS
ifeq ($(OS),Windows_NT)
	MKDIR_CMD = if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
else
	MKDIR_CMD = mkdir -p $(BUILD_DIR)
endif

# Default target
all: $(EXEC)

# Link object files to create executable
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJS)
#$(TARGET): $(OBJS)
#	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile source files to object files
$(BUILD_DIR)/%.o: src/%.cpp | make_build_dir
	$(CXX) $(CXXFLAGS) -c $< -o $@
#%.o: %.cpp
#	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create build directory
make_build_dir:
	$(MKDIR_CMD)

# Determine the OS
ifeq ($(OS),Windows_NT)
    CLEAN_CMD = del /F /Q $(TARGET).exe $(OBJS)
else
    CLEAN_CMD = rm -f $(TARGET) $(OBJS)
endif

# Clean up build files
clean:
	$(CLEAN_CMD)

.PHONY: all clean