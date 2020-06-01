/* 
 * solve.c - CS50 'solve' module
 *
 * see solve.h for more information.
 *
 * Valgrinders, May 2020
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <sudoku.h>
#include <create.h>
#include <solve.h>

/************ solve *************/
/* Given a valid sudoku data struct, solves this table and outputs the 
 * solution, which is the full table with all of the correct values. */
bool solve(sudoku_t* sudo)
{
    //if the table is already full, there is nothing to solve, return true
    if (is_full(sudo)){
        return true;
    }

    //traversing over the columns of the given table
    for (int x = 0; x < 9; x++) {

        //traversing over the rows of the given table
        for (int y = 0; y < 9; y++) {

            //when the value of a square in the board is 0, this signifies
            //an empty space which must be filled/solved 
            if (sudo->board[x][y] == 0) {

                //looping through the numbers 1-9 and testing if each option
                //is valid for the current empty space in the table 
                for (int n = 1; n <= 9; n++) {

                    //calling can_fit function in the sudoku module which 
                    //checks if the given value is valid for the column, row
                    //and square in which the empty space is found 
                    if (can_fit(sudo, x, y, n)) {

                         //if value is valid for all three parameters, set this 
                        //as the value for the empty space
                        sudo->board[x][y] = n;

                        //recursively checking if the table is full or if 
                        //the function must continue filling empty spaces
                        if (solve(sudo)){
                            
                            //if table is full, return true, otherwise the 
                            //function will continue looping through to find 
                            //values for all the empty spaces
                            return true;
                        }

                        //if table is not full, set this space to be 0, so it
                        //is recognized as an empty space 
                        sudo ->board[x][y] = 0;
                    }
                }

                //return false if current square in the table is not empty
                //and thus does not need to be handled
                return false;
            }
        }
    }

    //if the table is not full, but the function has reached this point, the 
    //given table is not solvable, return false 
    return false;
}
