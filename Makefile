# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -g

# Directories
SRCDIR = src
INCDIR = include
BINDIR = .

# Source files
SOURCES = $(wildcard $(SRCDIR)/main.cpp) $(wildcard $(SRCDIR)/dpll.cpp) 
OBJ = $(SRC:.cpp=.o)
EXECUTABLE = main

# Build target
all: $(EXECUTABLE)

# Rule to create executable
$(EXECUTABLE): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $@ $^
	
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean

clean:
	del main.exe

run: $(EXECUTABLE) 
	$(EXECUTABLE) $(arg)

run2: $(EXECUTABLE) 
	$(EXECUTABLE) 
