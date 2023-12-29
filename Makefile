# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wno-sign-compare -g 

# Directories
SRCDIR = src
INCDIR = include
BINDIR = .

# Source files
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
SELECTED_SOURCES =  $(wildcard $(SRCDIR)/main.cpp) $(wildcard $(SRCDIR)/dpll.cpp) $(wildcard $(SRCDIR)/printModel.cpp) $(wildcard $(SRCDIR)/chooseLiteral.cpp) $(wildcard $(SRCDIR)/parseDIMACS.cpp)
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

clean2: 
	del main2.exe

run: $(EXECUTABLE) 
	$(EXECUTABLE) $(arg)

run2: $(EXECUTABLE2) 
	$(EXECUTABLE2) $(arg)
