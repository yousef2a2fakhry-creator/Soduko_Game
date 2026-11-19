#include <iostream>
#include"SudokuGame.h"
#include <bits/stdc++.h>
using namespace std;


signed main() {

#include <vector>

    // std::vector<std::vector<int>> test = {
    //     {5, 3, 0, 0, 7, 0, 0, 0, 0},
    //     {6, 0, 0, 1, 9, 5, 0, 0, 0},
    //     {0, 9, 8, 0, 0, 0, 0, 6, 0},
    //     {8, 0, 0, 0, 6, 0, 0, 0, 3},
    //     {4, 0, 0, 8, 0, 3, 0, 0, 1},
    //     {7, 0, 0, 0, 2, 0, 0, 0, 6},
    //     {0, 6, 0, 0, 0, 0, 2, 8, 0},
    //     {0, 0, 0, 4, 1, 9, 0, 0, 5},
    //     {0, 0, 0, 0, 8, 0, 0, 7, 9}};

        SudokuGame test;
        while (true)
        {
            label:
            try
            {
                test.Display_Menu();
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
            goto label;
            
        }
        


    return 0;
}