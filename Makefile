# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -g

# Directories
SRCDIR = src
INCDIR = include
BINDIR = .

# Source files
SOURCES = $(wildcard $(SRCDIR)/main.cpp) $(wildcard $(SRCDIR)/dpll.cpp) 
EXECUTABLE = main

# Build target
all: $(EXECUTABLE)

# Rule to create executable
$(EXECUTABLE): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $@ $^ 

.PHONY: clean

clean:
	del main.exe

run: $(EXECUTABLE) 
	$(EXECUTABLE) $(arg)
