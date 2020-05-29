/*
Header file for sudoku.c
*/

#ifndef __SUDOKU_H
#define __SUDOKU_H

/**************** global types ****************/
typedef struct sudoku sudoku_t;

/**************** functions ****************/

/*
Given a table it will print the table in the correct format
*/
void print_table(int table [9][9]);

/*
Checks if a given value n will
fit at position x, y
*/
bool can_fit(int x, int y, int n);
bool can_fit_column(int x, int y, int n)
bool can_fit_square(int x, int y, int n)
bool can_fit_row(int x, int y, int n)

/*
Solves the puzzle using recursion
*/
bool solve();

/*
Reads a table given a file, returns false if invalid
*/
bool read_table(FILE *fp);

/*
Checks if there are any zeros in a table
*/
bool is_full(int table [9][9]);


#endif