CXX := g++
CXXFLAGS ?= -std=c++17 -O2 -Wall -Wextra
TARGET := sudoku.exe
SOURCES := main.cpp SudokuGame.cpp SudokuBoard.cpp SudokuSolver.cpp
OBJECTS := $(SOURCES:.cpp=.o)
HEADERS := SudokuGame.h SudokuBoard.h SudokuSolver.h

# Detect OS to select the correct delete command
ifeq ($(OS),Windows_NT)
    CLEAN_CMD = del /F /Q $(subst /,\,$(OBJECTS) $(TARGET)) 2>nul || exit 0
else
    CLEAN_CMD = rm -f $(OBJECTS) $(TARGET)
endif

.PHONY: all run clean

all: $(TARGET)

run: $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@

$(OBJECTS): $(HEADERS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(CLEAN_CMD)