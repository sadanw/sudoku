/*
 * fuzzsudoku.c - a program to perform fuzztesting of our sudoku creator/solver
 * Valgrinders, May 2020
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>

#include "common/solve.h"
#include "common/create.h"
#include "common/sudoku.h"

/* Function headers */
bool isPositiveNumber(char number[]);
bool compare_boards(sudoku_t* sudo1, sudoku_t* sudo2);
bool isValidSolution(sudoku_t* sudo);
void copy_sudoku(sudoku_t* sudo, sudoku_t* copy);
bool can_fit_fuzz(sudoku_t* sudo, int x, int y, int n);
bool can_fit_column_fuzz(sudoku_t* sudo, int x, int y, int n);
bool can_fit_row_fuzz(sudoku_t* sudo, int x, int y, int n);
bool can_fit_square_fuzz(sudoku_t* sudo, int x, int y, int n);

int main(const int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: ./fuzzsudoku numTest\n");
        return 1;
    }

    if (!isPositiveNumber(argv[1])) {
        fprintf(stderr, "Usage: ./fuzzsudoku numTest\n");
        return 1;
    }

    else {
        int numTest = atoi(argv[1]);
        for (int i = 0; i < numTest; i++) {
            sudoku_t* new = create();
            int numSolutions = 0;
          
            printf("--------------------------------------------------\n");
            printf("Generated board #%d: \n", i);
            print_board(new);

            // make a copy of the new board
            sudoku_t* copy = sudoku_new();
            copy_sudoku(new, copy);

            sudoku_t* copy2 = sudoku_new();
            copy_sudoku(new, copy2);

            // solve the board and ensure it is unique
            numSolutions = uni_solve(copy2, 0);
            solve(new);

            printf("Solved board #%d: \n", i);
            print_board(new);

            if (numSolutions == 0) {
                printf("Created board has no solution.\n");
            }
            else if (numSolutions > 1) {
                printf("Created board has %d solutions.\n", numSolutions);
            }
            else {
                printf("Created board has %d solution.\n", numSolutions);
            }

            // check board follows sudoku rules
            if (!isValidSolution(new)) {
                printf("Solution is not valid.\n");
            }
            else {
                printf("Solution is valid.\n");
            }

            // check the solver did not modify original values in board
            if (!compare_boards(new, copy)) {
                printf("Solving the sudoku modified the original values in the board.\n");
            }
            else {
                printf("Solving the sudoku did not modify the original values in the board.\n");
            }

            // clean up
            if (new != NULL) {
                delete_sudoku(new);
            }

            if (copy != NULL) {
                delete_sudoku(copy);
            }

            if (copy2 != NULL) {
                delete_sudoku(copy2);
            }
        }
    }
    return 0;
}

/***************** compare_boards *****************
 * caller provides two sudoku structures
 * returns false if any non-zero numbers differ, true otherwise
 */
bool compare_boards(sudoku_t* sudo1, sudoku_t* sudo2) {
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            if ((get_value(sudo1, i, j) != 0) && (get_value(sudo2, i, j) != 0)) {
                if ((get_value(sudo1, i, j)) != (get_value(sudo2, i, j))) {
                    return false;
                }
            }
        }
    }
    return true;
}

/***************** isValidSolution *****************
 * returns true if a completed sudoku board follows the rules of sudoku
 * caller must pass a completely filled sudoku board
 */
bool isValidSolution(sudoku_t* sudo) {
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            if (!can_fit_fuzz(sudo, i, j, get_value(sudo, i, j))) {
                return false;
            }
        }
    }
    return true;
}

/************ can_fit_fuzz() **********/
/* Checks to see that the given value, n, is valid with regards to the column, row, 
 * and the square in which the x, y square is found. */
bool can_fit_fuzz(sudoku_t* sudo, int x, int y, int n){

    //calling each of the three helper functions to test each of the requirements 
    return can_fit_column_fuzz(sudo, x, y, n) && can_fit_row_fuzz(sudo, x, y, n) && can_fit_square_fuzz(sudo, x, y, n);
}

/*************** can_fit_column_fuzz() ***********/
/* Checking to see if the value is valid for the column. */
bool can_fit_column_fuzz(sudoku_t* sudo, int x, int y, int n){
    //traversing over the column in which the square at coordinates
    //x, y is found 
    for (int i = 0; i < 9; i++) {
            //if this value is already in the column, return false 
            //because the same value cannot be found twice within a column
            if (i != y) {
                if (get_value(sudo, x, i) == n){
                    return false;
                }
        }
    }
    //if the value is not already in the column, return true 
    return true;
}

/************ can_fit_row_fuzz() *************/
/* Checking to see if the value is valid for the row. */
bool can_fit_row_fuzz(sudoku_t* sudo, int x, int y, int n){
    //traversing over the row in which the square at coordinates
    //x, y is found
    for (int i = 0; i < 9; i++){
            //if this value is already in the row, return false
            //because the same value cannot be found twice within a row
            if (i != x) { 
                if (get_value(sudo, i, y) == n){
                    return false;
                }
        }
    }
    //if the value is not already in the row, return true 
    return true;
}

/********** can_fit_square_fuzz() *************/
/* Checks if a given value, n, is valid for the position at x, y in the 
 * sudoku board. */
bool can_fit_square_fuzz(sudoku_t* sudo, int x, int y, int n) {   
    //creating new variables so that the full 3x3 square can be traversed
    int xval = (x / 3) * 3;
    int yval = (y / 3) * 3;
    //looping through columns of 3x3 square
    for (int i = 0; i < 3; i++){
	//looping through rows of 3x3 square
        for (int j = 0; j < 3; j++){
            //if the given value, n, is already found within the table,
	        //return false because a value cannot be found twice within
	        //a 3x3 set of squares in the table 
            if (((xval + i) != x) && ((yval + j) != y)) {
                if (get_value(sudo, xval + i, yval + j) == n){
                    return false;
                }
            }
        }
    }
    return true;
}


/***************** isPositiveNumber *****************
 * takes a char[], returns whether or not it can be converted to an int
 * modified from: https://stackoverflow.com/a/29248688
 */
bool isPositiveNumber(char number[]) {
    int i = 0;

    //checking for negative numbers
    if (number[0] == '-') {
        return false;
    }
    for (; number[i] != 0; i++)
    {
        //if (number[i] > '9' || number[i] < '0')
        if (!isdigit(number[i])) {
            return false;
        }
    }
    return true;
}
