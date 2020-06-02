/*
 * sudoku.h - header file for CS50 sudoku module
 *
 * A *sudoku* is a well known logic puzzle where numbers between 1 and 9 are
 * placed on a 9x9 grid of cells, making sure that there are no repeated numbers
 * within each column, row, and set of 3x3 squares. The sudoku data struct holds
 * a 9x9 2D list which holds the values for each position in the table. It also
 * holds a 9x9x9 3D list which holds the potential values for each of the 
 * squares in the table. 
 *
 * Valgrinders, May 2020
 */

#ifndef __SUDOKU_H
#define __SUDOKU_H

/**************** global types ****************/
typedef struct sudoku sudoku_t;

/**************** functions ****************/

/************ sudoku_new *****************/
/* Create a new (empty) sudoku.
 *
 * Caller provides:
 *      nothing.
 * We return:
 *      pointer to the new sudoku; return NULL if error.
 * We guarantee:
 *      sudoku is initialized to empty.
 * Caller is responsible for:
 *      later calling sudoku_delete.
 */
sudoku_t *sudoku_new(void);

/*
Creates a fully formed sudoku puzzle, returns NULL on error
Caller is responsible for freeing the sudoku struct later
*/
// sudoku_t* create();

/************** fill_square ***************/
/* Fills a set of 3x3 squares of the given sudoku board, with x and y being
 * the upper left coordinates of the 3x3 square. 
 *
 * Caller provides:
 *      valid pointer to a sudoku data struct, x and y integers which are the 
 *      coordinates for the upper right square. 
 * We return:
 *      nothing. The given sudoku struct has been initialized in one set of 
 *      3x3 squares. 
 */
void fill_square(sudoku_t *sudo, int x, int y);

/************* fill_board ***********/
/* Fills an entire sudoku board with random, valid values.
 *
 * Caller provides:
 *      valid pointer to a sudoku data struct.
 * We return:
 *      a boolean indicating if the given sudoku table had a possible solution.
 *      False if no solution found, true otherwise. In addition, the given
 *      sudoku data struct is initialized with valid values.
 */
bool fill_board(sudoku_t* sudo);

/*************** remove_num ***************/
/* Randomly removes a specified number of values from a sudoku board. 
 *
 * Caller provides:
 *      a valid pointer to a sudoku data struct and an integer value which 
 *      is the number of values to remove from the given table.
 * We return:
 *      nothing, but the given sudoku struct is modified so that it now has
 *      num number of empty species which is signified by 0's. 
 */
void remove_num(sudoku_t* sudo, int num);

/*
Solves the puzzle using recursion
*/
// bool solve(sudoku_t* sudo);

// int uni_solve(sudoku_t* sudo, int sol);

/**************** print_board *************/
/* Prints the contents of the given sudoku table in a 9x9 format.
 *
 * User provides:
 *      a valid pointer to a sudoku data struct.
 * We return:
 *      nothing, but the given contents of the given sudoku table are printed
 *      to stdout. 
 */
void print_board(sudoku_t* sudo);

/*************** load_board ************/
/* Reads a sukoku board from a given a file.
 * 
 * User provides: 
 *      valid file pointer.
 * We return:
 *      a valid pointer to a new sudoku data struct which was initialized using
 *      the contents found in the given file pointer. 
 */
sudoku_t* load_board(FILE *fp);

/************* is_full ****************/
/* Checks if there are any zeros, signifying empty spaces in the given sudoku 
 * board.
 *
 * User provides:
 *      valid pointer to sudoku data struct.
 * We return:
 *      boolean indicating if the given sudoku table was full, true, or had 
 *      empty spaces, false. 
 */
bool is_full(sudoku_t* sudo);

/************** can_fit ***************/
/* Checks if a given value n will fit at position x, y in a sudoku board.
 *
 * User provides: 
 *      valid pointer to sudoku data struct, x and y coordinates in sudoku
 *      board, and the value, n, to determine if it is valid in that position.
 * We return: 
 *      a boolean indicating whether the given value is valid for the position
 *      x, y in the table. 
 */
bool can_fit(sudoku_t* sudo, int x, int y, int n);

/*************** can_fit_column *************/
/* Checks to see if a given value, n, will fit at position x, y, in a sudoku 
 * board, with regards to the column in which it is found. The same position 
 * cannot be found twice within the same column.
 *
 * User provides:
 *      valid pointer to sudoku data struct, x and y coordinates in sudoku
 *      board, and the value, n, to determine if it is valid in that column.
 * We return: 
 *      a boolean indicating whether the given value is valid for the column,
 *      x, in the table.
 */
bool can_fit_column(sudoku_t* sudo, int x, int y, int n);

/*************** can_fit_row *************/
/* Checks to see if a given value, n, will fit at position x, y, in a sudoku
 * board, with regards to the row in which it is found. The same position
 * cannot be found twice within the same row.
 *
 * User provides:
 *      valid pointer to sudoku data struct, x and y coordinates in sudoku
 *      board, and the value, n, to determine if it is valid in that row.
 * We return:
 *      a boolean indicating whether the given value is valid for the row,
 *      y, in the table.
 */
bool can_fit_row(sudoku_t* sudo, int x, int y, int n);

/*************** can_fit_square *************/
/* Checks to see if a given value, n, will fit at position x, y, in a sudoku
 * board, with regards to the square in which it is found. The same position
 * cannot be found twice within the same square.
 *
 * User provides:
 *      valid pointer to sudoku data struct, x and y coordinates in sudoku
 *      board, and the value, n, to determine if it is valid in that square.
 * We return:
 *      a boolean indicating whether the given value is valid for the square
 *      in which it is found in the table.
 */
bool can_fit_square(sudoku_t* sudo, int x, int y, int n);

/***************** shuffle *************/
/* From: https://stackoverflow.com/a/6127606
 * Arranges the N elements of ARRAY in random order.
 * Only effective if N is much smaller than RAND_MAX;
 * if this may not be the case, use a better random
 * number generator. 
 *
 * User provides:
 *      valid pointer to a list of integers and a value which is the number
 *      of integers within the list. 
 * We return: 
 *      nothing, but the given array/list has been shuffled in place. 
 */
void shuffle(int *array, size_t n);

/************* delete_sudoku *************/
/* Frees the memory associated with the given data struct as long as it is
 * not NULL.
 *
 * User provides:
 * 	valid pointer to sudoku data struct.
 * We return:
 * 	nothing, but the memory associated with given data struct is 
 * 	freed as long as it is not NULL. 
 */
void delete_sudoku(sudoku_t* sudo);

void copy_sudoku(sudoku_t* sudo, sudoku_t* copy);

/***************** compare_boards *****************
 * caller provides two sudoku structures
 * returns false if any non-zero numbers differ, true otherwise
 */
bool compare_boards(sudoku_t* sudo1, sudoku_t* sudo2);

/***************** isValidSolution *****************
 * returns true if a completed sudoku board follows the rules of sudoku
 * caller must pass a completely filled sudoku board
 */
bool isValidSolution(sudoku_t* sudo);

int testfunc();

#endif
