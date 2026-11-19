#ifndef SOLVER_H
#define SOLVER_H
#include <vector>
#include "SudokuGame.h"
class SudokuSolver
{
private:
    SudokuBoard board_copy_for_solving;
    

public:
    SudokuSolver(SudokuBoard board);
    void solve();
    bool findMRV(int & row , int & coloum);
    bool take_step();
};

#endif