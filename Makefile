# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Directories
SRCDIR = src
BINDIR = .

# Source files
SOURCES = $(wildcard $(SRCDIR)/main.cpp)
EXECUTABLE = main

# Build target
all: $(EXECUTABLE)

# Rule to create executable
$(EXECUTABLE): $(SOURCES)
	$(CXX) $(CXXFLAGS) $^ -o $@

.PHONY: clean

clean:
	rm -f $(EXECUTABLE)

run: $(EXECUTABLE)
	$(EXECUTABLE) $(arg)
