# Sudoku Game & Solver

A console Sudoku game written in C++. You can play interactively, auto-solve any puzzle, and load or save boards from text files. It supports NxN boards such as 9x9 and 16x16.

## Features
- Interactive menu: enter or remove a value
- Automatic solver using backtracking with the MRV (Minimum Remaining Values) heuristic
- Load puzzles from a file and save the current board
- Supports 9x9, 16x16, and other perfect-square board sizes

## Build and Run
Requires `g++`.

```bash
make
./a.out
```

If your Makefile names the executable differently, use that name instead.

## Puzzle File Format
- Numbers separated by spaces
- Use `.` or `0` for an empty cell
- `|` separators are optional

Example (9x9):
```
5 3 0 0 7 0 0 0 0
6 0 0 1 9 5 0 0 0
0 9 8 0 0 0 0 6 0
...
```

Sample puzzles are in the `puzzles/` folder.

## Project Structure
- `SudokuBoard`: board state and rule validation
- `SudokuGame`: menu, file loading and saving
- `SudokuSolver`: backtracking solver with MRV
- `main.cpp`: entry point
