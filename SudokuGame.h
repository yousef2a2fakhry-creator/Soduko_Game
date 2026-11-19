#ifndef GAME_H
#define GAME_H
#include "SudokuBoard.h"
#include "SudokuSolver.h"
#include <fstream>
class SudokuGame
{
private:
    SudokuBoard Sudoku;
    static std::fstream input;
    static std::fstream output;

public:
    SudokuGame(const std::vector<std::vector<int>> &data);
    SudokuGame();
    virtual ~SudokuGame();
    static void Save_Board(SudokuBoard &board, const std::string &file_name);
    static void Load_Board(SudokuBoard &board, const std::string &file_name);
    virtual void Display_Menu();
};

#endif