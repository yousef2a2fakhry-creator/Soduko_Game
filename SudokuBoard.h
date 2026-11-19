#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <string>
#include <unordered_map>
class SudokuGame;
class SudokuBoard
{
private:
    std::vector<std::vector<int>> Board;

    std::vector<std::vector<int>> coloums;
    std::vector<std::vector<int>> rows;
    std::vector<std::vector<int>> grid;

public:
    SudokuBoard();
    virtual void Assign_Sudoku(const std::vector<std::vector<int>> &data);
    virtual void Set_Value(int row, int coloum, int number);
    virtual void Remove_Value(int row, int coloum);
    virtual int GetValue(int row, int coloum) const;
    virtual int GetSize() const;
    virtual void print_board() const;
    virtual bool IsValidSudoku(int row, int coloum, int number) const;
};
#endif