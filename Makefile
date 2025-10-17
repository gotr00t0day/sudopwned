# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

# Directories
SRC_DIR = .
MODULES_DIR = modules

# Source files
SRCS = $(SRC_DIR)/main.cpp \
       $(MODULES_DIR)/sudopwn.cpp \
       $(MODULES_DIR)/executils.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Output binary
TARGET = sudopwned

# Default build
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rebuild if headers change
$(MODULES_DIR)/sudopwn.o: $(MODULES_DIR)/sudopwn.h
$(MODULES_DIR)/executils.o: $(MODULES_DIR)/executils.h

# Clean build artifacts
clean:
	rm -f $(OBJS) $(TARGET)

# Force rebuild
rebuild: clean all

.PHONY: all clean rebuild

