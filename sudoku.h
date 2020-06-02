/*
Header file for sudoku.c
*/

#ifndef __SUDOKU_H
#define __SUDOKU_H

/**************** global types ****************/
typedef struct sudoku sudoku_t;

/**************** functions ****************/

/*
Creates a fully formed sudoku puzzle, returns NULL on error
Caller is responsible for freeing the sudoku struct later
*/
sudoku_t* create();

/*
Fills a 3x3 square of the sudoku board, where x and y are the upper left coordinates of the square
*/
void fill_square(sudoku_t* sudo, int x, int y);

/*
Fills an entire sudoku board with random, valid values
*/
bool fill_board(sudoku_t* sudo);

/*
Randomly removes a specified number of values from a sudoku board
*/
void remove_num(sudoku_t* sudo, int num);

/*
Solves the puzzle using recursion
*/
bool solve(sudoku_t* sudo);

/*
Given a sudoku_t struct it will print the board in the correct format
*/
void print_board(sudoku_t* sudo);

/*
Reads a sukoku board from a given a file, returns NULL if invalid
*/
sudoku_t* load_board(FILE *fp);

/*
Checks if there are any zeros in a sudoku board
*/
bool is_full(sudoku_t* sudo);

/*
Checks if a given value n will fit at position x, y in a sudoku board
*/
bool can_fit(sudoku_t* sudo, int x, int y, int n);

bool can_fit_column(sudoku_t* sudo, int x, int y, int n);

bool can_fit_row(sudoku_t* sudo, int x, int y, int n);

bool can_fit_square(sudoku_t* sudo, int x, int y, int n);

/*  From: https://stackoverflow.com/a/6127606
    Arrange the N elements of ARRAY in random order.
    Only effective if N is much smaller than RAND_MAX;
    if this may not be the case, use a better random
    number generator. 
   */
void shuffle(int *array, size_t n);

#endif