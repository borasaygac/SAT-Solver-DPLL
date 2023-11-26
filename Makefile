# Compiler and flags
CXX = g++

CLANG := clang++
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	CXX := $(CLANG)
endif

CXXFLAGS = -std=c++11 -Wall

# Directories
SRCDIR = src
BINDIR = bin

# Source files
SOURCES = $(wildcard $(SRCDIR)/main.cpp)
EXECUTABLES = $(patsubst $(SRCDIR)/%.cpp,$(BINDIR)/%,$(SOURCES))

# Default target
all: $(EXECUTABLES)

# Rule to create executables
$(BINDIR)/%: $(SRCDIR)/%.cpp | $(BINDIR)
	$(CXX) $(CXXFLAGS) $< -o $@

$(BINDIR):
	mkdir -p $(BINDIR)

.PHONY: clean

clean:
	rm -rf $(BINDIR)

run: $(EXECUTABLES)
	./$(BINDIR)/main $(arg)
