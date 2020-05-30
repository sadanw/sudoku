#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <sudoku.h>
#include <create.h>
#include <solve.h>

bool solve(sudoku_t* sudo){
    if (is_full(sudo)){
        return true;
    }


    for (int x = 0; x < 9; x++){
        for (int y = 0; y < 9; y++){
            if (sudo->board[x][y] == 0){
                for (int n = 1; n <= 9; n++) { 
                    if (can_fit(sudo, x, y, n)) { 
                        sudo->board[x][y] = n; 
                        if (solve(sudo)){
                            return true;
                        }
                        sudo->board[x][y] = 0; 
                    } 
                } 
                return false; 
            }
        }
    }
    return false;
}