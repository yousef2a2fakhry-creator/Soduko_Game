#include "SudokuSolver.h"
#include <iostream>
using namespace std;
#include <cmath>
SudokuSolver::SudokuSolver(SudokuBoard board)
{
    board_copy_for_solving = board;
}
bool SudokuSolver::findMRV(int &row, int &coloum)
{
    bool empty_cell_found = false;
    int size = board_copy_for_solving.GetSize();
    int MRV = size + 1;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (board_copy_for_solving.GetValue(i, j) == 0)
            {
                int current_value = 0;
                for (int num = 1; num <= size; num++)
                {
                    if (board_copy_for_solving.IsValidSudoku(i, j, num))
                    {
                        current_value++;
                    }
                }
                if (current_value < MRV)
                {
                    MRV = current_value;
                    row = i;
                    coloum = j;
                    empty_cell_found = true;
                }
            }
        }
    }
    return empty_cell_found;
}
bool SudokuSolver::take_step()
{
    int size = board_copy_for_solving.GetSize();
    int row = -1;
    int coloum = -1;
    if (!findMRV(row, coloum))
    {
        return true;
    }
    for (int i = 1; i <= size; i++)
    {
        if (board_copy_for_solving.IsValidSudoku(row, coloum, i))
        {
            board_copy_for_solving.Set_Value(row, coloum, i);
            if (take_step())
            {
                return true;
            }

            board_copy_for_solving.Remove_Value(row, coloum);
        }
    }
    return false;
}
void SudokuSolver::solve()
{
    if (take_step())
    {
        cout << "Board solved" << endl;
        board_copy_for_solving.print_board();
        cout << "=====================================" << endl;
        cout << "Do tou want to save the solution ? \n"
             << "1) YES\n"
             << "2) NO\n";
        string choice;
        cin >> choice;
        if (choice == "YES")
        {
            string name;
            cout << "Enter the file name you need to save with " << endl;
            cin.ignore(10000, '\n');
            getline(cin, name);
            SudokuGame::Save_Board(board_copy_for_solving, name);
        }
    }
    else
    {
        cout << "No solution found" << endl;
    }
}
