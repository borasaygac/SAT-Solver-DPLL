# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wno-sign-compare -g 

# Directories
SRCDIR = src
INCDIR = include
BINDIR = .

# Source files
SOURCES = $(wildcard $(SRCDIR)/main.cpp) $(wildcard $(SRCDIR)/dpll.cpp) $(wildcard $(SRCDIR)/checkAllClauses.cpp) $(wildcard $(SRCDIR)/chooseLit.cpp)   
SOURCES2 = $(wildcard $(SRCDIR)/main2.cpp) $(wildcard $(SRCDIR)/cnf2.cpp) $(wildcard $(SRCDIR)/dpll.cpp) $(wildcard $(SRCDIR)/checkAllClauses.cpp) $(wildcard $(SRCDIR)/parseDimacs.cpp) 

OBJ = $(SRC:.cpp=.o)
EXECUTABLE = main
EXECUTABLE2 = main2

# Build target
all: $(EXECUTABLE)

# Rule to create executable
$(EXECUTABLE): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $@ $^

$(EXECUTABLE2) : $(SOURCES2)
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
