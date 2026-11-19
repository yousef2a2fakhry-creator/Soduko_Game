#include "SudokuGame.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <cmath>
#include <iomanip>
#include <sstream>
using namespace std;

std::fstream SudokuGame::output;
std::fstream SudokuGame::input;

SudokuGame::SudokuGame()
{
}
SudokuGame::SudokuGame(const std::vector<std::vector<int>> &data)
{
    Sudoku.Assign_Sudoku(data);
}
SudokuGame::~SudokuGame()
{
    SudokuGame::input.close();
    SudokuGame::output.close();
}
void SudokuGame::Display_Menu()
{
    Sudoku.print_board();
    int size = Sudoku.GetSize();
    cout << "Enter a choice:\n"
         << "1) Enter a move\n"
         << "2) Solve automatically\n"
         << "3) Load puzzle from file\n"
         << "4) Save current puzzle to file\n"
         << "5) Exit\n"
         << "Choice: \n";
    int chioce;
    cin >> chioce;
    cin.ignore(10000, '\n');
    if (chioce == 1)
    {
        int which;
        cout << "Remove a value or set a value ? press 1 or 2 \n"
             << "1) Enter a value\n"
             << "2) remove a value\n";
        cin >> which;
        if (which == 1)
        {

            int row;
            int coloum;
            int number;
            cout << "Enter Row (1-" << size << "): ";
            cin >> row;
            cout << "Enter Column (1-" << size << "): ";
            cin >> coloum;
            cout << "Enter Number (1-" << size << "): ";
            cin >> number;
            row--;
            coloum--;
            if (Sudoku.IsValidSudoku(row, coloum, number))
            {
                Sudoku.Set_Value(row, coloum, number);
            }
            else
            {
                throw invalid_argument("SudokuGame::inputs are not correct");
            }
        }
        else if (which == 2)
        {

            int row;
            int coloum;
            cout << "Enter Row (1-" << size << "): ";
            cin >> row;
            cout << "Enter Column (1-" << size << "): ";
            cin >> coloum;
            row--;
            coloum--;
            if (Sudoku.GetValue(row, coloum) == 0)
            {
                cout << "Value is already empty \n";
            }
            else
            {
                Sudoku.Remove_Value(row, coloum);
            }
        }
    }
    else if (chioce == 2)
    {
        SudokuSolver solved_board(Sudoku);
        solved_board.solve();
    }

    else if (chioce == 3)
    {
        cout << "Enter the file name you need to load  " << endl;
        string file_name;
        getline(cin, file_name);
        SudokuGame::Load_Board(Sudoku, file_name);
    }

    else if (chioce == 4)
    {
        cout << "Enter the file name you need to save in " << endl;
        string file_name;
        getline(cin, file_name);
        SudokuGame::Save_Board(Sudoku, file_name);
    }

    else if (chioce == 5)
    {
        cout << "Saving the current board in file named SAVED.TXT";
        Save_Board(Sudoku, "SAVED BOARD.TXT");
        exit(0);
    }

    else
    {
        cerr << "invalid choice " << endl;
    }
}
void SudokuGame::Load_Board(SudokuBoard &board, const std::string &file_name)
{
    if (SudokuGame::input.is_open())
    {
        SudokuGame::input.close();
    }
    SudokuGame::input.clear();
    SudokuGame::input.open(file_name, ios::in);
    if (!SudokuGame::input.is_open())
    {
        throw runtime_error("Something went wrong when opening the file");
    }

    vector<vector<int>> temp_board;
    string str;

    while (getline(SudokuGame::input, str))
    {
        vector<int> row;
        string token;
        stringstream row_stream(str);
        while (row_stream >> token)
        {
            if (token == ".")
            {
                row.push_back(0);
            }
            else if (token == "|")
            {
                continue;
            }
            else
            {
                int value;
                stringstream token_stream(token);
                if (token_stream >> value && token_stream.eof())
                {
                    row.push_back(value);
                }
            }
        }
        if (!row.empty())
        {
            temp_board.push_back(row);
        }
    }
    SudokuGame::input.close();
    try
    {
        board.Assign_Sudoku(temp_board);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void SudokuGame::Save_Board(SudokuBoard &board, const std::string &file_name)
{
    if (SudokuGame::output.is_open())
    {
        SudokuGame::output.close();
    }
    SudokuGame::output.clear();
    SudokuGame::output.open(file_name, ios::out | ios::trunc);

    if (!SudokuGame::output.is_open())
    {
        throw runtime_error("Something went wrong when opening the file");
    }

    int size = board.GetSize();
    int boxSize = static_cast<int>(std::sqrt(size));
    int cellWidth = static_cast<int>(std::to_string(size).length()) + 1;

    auto print_separator = [&]()
    {
        for (int box = 0; box < boxSize; box++)
        {
            if (box > 0)
            {
                SudokuGame::output << "+";
            }
            SudokuGame::output << string((cellWidth + 1) * boxSize + 1, '-');
        }
        SudokuGame::output << endl;
    };

    for (int i = 0; i < size; i++)
    {
        if (i > 0 && i % boxSize == 0)
        {
            print_separator();
        }

        for (int j = 0; j < size; j++)
        {
            if (j > 0 && j % boxSize == 0)
            {
                SudokuGame::output << "| ";
            }

            try
            {
                int n = board.GetValue(i, j);
                if (n == 0)
                {
                    SudokuGame::output << setw(cellWidth) << "." << " ";
                }
                else
                {
                    SudokuGame::output << setw(cellWidth) << n << " ";
                }
            }
            catch (const std::out_of_range &e)
            {
                cerr << e.what() << '\n';
            }
            catch (const std::exception &e)
            {
                cerr << e.what() << '\n';
            }
        }
        SudokuGame::output << endl;
    }
    SudokuGame::output.close();
}