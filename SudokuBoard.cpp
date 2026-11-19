#include "SudokuBoard.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <string>
#include <stdexcept>

using namespace std;

SudokuBoard::SudokuBoard()
{
}

/*
   All loop counters that interact with .size() has been written as size_t
    cuz the return type is unsigend int ==> it makes warnings when compile
*/
void SudokuBoard::Assign_Sudoku(const std::vector<std::vector<int>> &data)
{
    size_t size = data.size();
    int boardSize = data.size();

    Board.assign(size, vector<int>(size, 0));
    coloums.assign(size, vector<int>(size + 1, 0));
    rows.assign(size, vector<int>(size + 1, 0));
    grid.assign(size, vector<int>(size + 1, 0));

    size_t boxSize = std::sqrt(size);

    for (size_t i = 0; i < size; i++)
    {
        if (data[i].size() != size)
        {
            throw invalid_argument("Board is not square");
        }
        for (size_t j = 0; j < size; j++)
        {
            if (data[i][j] >= 0 && data[i][j] <= boardSize)
            {
                int number = data[i][j];
                Board[i][j] = number;
                if (number != 0)
                {
                    size_t g = (i / boxSize) * boxSize + (j / boxSize);
                    if (this->rows[i][number] > 0 || this->coloums[j][number] > 0 || this->grid[g][number] > 0)
                    {
                        throw invalid_argument("Initial board state contains duplicate numbers");
                    }
                    this->rows[i][number]++;
                    this->coloums[j][number]++;
                    this->grid[g][number]++;
                }
            }
            else
            {
                throw invalid_argument("The number can't be assigned in the Board according to the rules");
            }
        }
    }
}

void SudokuBoard::print_board() const
{
    if (Board.empty())
    {
        cout << "(Board is currently empty. Load a puzzle first!)\n\n";
        return;
    }
    size_t size = Board.size();
    size_t boxSize = std::sqrt(size);
    int cellWidth = std::to_string(size).length() + 1;

    auto print_separator = [&]()
    {
        for (size_t box = 0; box < boxSize; box++)
        {
            if (box > 0)
            {
                cout << "+";
            }
            cout << string((cellWidth + 1) * boxSize + 1, '-');
        }
        cout << endl;
    };

    for (size_t i = 0; i < size; i++)
    {
        if (i > 0 && i % boxSize == 0)
        {
            print_separator();
        }

        for (size_t j = 0; j < size; j++)
        {
            if (j > 0 && j % boxSize == 0)
            {
                cout << "| ";
            }

            string value = Board[i][j] == 0 ? "." : to_string(Board[i][j]);
            cout << setw(cellWidth) << value << " ";
        }
        cout << endl;
    }
}

void SudokuBoard::Set_Value(int row, int coloum, int number)
{
    int size = Board.size();
    int N = std::sqrt(size);
    if (row < 0 || row >= size || coloum < 0 || coloum >= size || number <= 0 || number > size)
    {
        throw invalid_argument("Value of the column and the row are invalid");
    }
    if (IsValidSudoku(row, coloum, number))
    {
        if (Board[row][coloum] != 0)
        {
            Remove_Value(row, coloum);
        }
        Board[row][coloum] = number;
        int g = (row / N) * N + coloum / N;
        this->rows[row][number]++;
        this->coloums[coloum][number]++;
        this->grid[g][number]++;
    }
    else
    {
        throw invalid_argument("The number can't be assigned in the Board according to the rules");
    }
}

int SudokuBoard::GetValue(int row, int coloum) const
{
    int size = Board.size();
    if (row < 0 || row >= size || coloum < 0 || coloum >= size)
    {
        throw std::out_of_range("Row or column is out of bounds");
    }
    return Board[row][coloum];
}

void SudokuBoard::Remove_Value(int row, int coloum)
{
    int size = Board.size();
    if (row < 0 || row >= size || coloum < 0 || coloum >= size || Board[row][coloum] == 0)
    {
        throw std::out_of_range("Row or column is out of bounds or there is no number here");
    }
    int N = std::sqrt(size);
    int temp = Board[row][coloum];
    Board[row][coloum] = 0;
    int g = (row / N) * N + coloum / N;
    this->rows[row][temp]--;
    this->coloums[coloum][temp]--;
    this->grid[g][temp]--;
}

int SudokuBoard::GetSize() const
{
    return Board.size();
}

bool SudokuBoard::IsValidSudoku(int row, int coloum, int number) const
{
    int size = Board.size();
    if (row < 0 || row >= size || coloum < 0 || coloum >= size || number <= 0 || number > size)
    {
        return false;
    }
    int N = std::sqrt(size);
    int g = (row / N) * N + coloum / N;
    if (this->rows[row][number] != 0 || this->coloums[coloum][number] != 0 || this->grid[g][number] != 0)
    {
        return false;
    }

    return true;
}