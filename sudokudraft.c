/*
 * sudoku.c - CS50 'sudoku' module
 *
 * see sudoku.h for more information
 *
 * Team, April 2020
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "sudoku.h"


/****************** file-local global variables **************/
/* none */

/******************** local types **************/
typedef struct square{
        int value;      //value the square holds
        int options[9]; //list of potential integers that could be the value
} square_t;

/***************** global types ****************/
typedef struct sudoku{
    int board[9][9];    //2D array of all of the squares in the board
    int options[9][9][9];
} sudoku_t;

/************* global functions *************/
/* visible outside this file */
/* see sodoku.h for comments about exported functions */

/***************** local functions **************/
/* not visible outside this file */

/******************* sudoku_new() **************/
/* Create a new (empty) sudoku. Returns pointer to new sodoku, or NULL if 
 * error. */
sudoku_t *sudoku_new(void)
{
        //allocating memory for the sodoku data struct
        sudoku_t *sudoku = count_malloc(sizeof(sudoku_t));

        //returning NULL if there is an error creating the sodoku
        if (sudoku == NULL) {
                return NULL;
        }

        //otherwise return pointer to new sodoku struct
        else {
                //looping through the board and initializing all the values to zero
                for (int x = 0; x < 9; x++) {
                        for (int y = 0; y < 0; y++) {
                                sudoku->board[x][y] = 0;
                        }
                }
                //returning point to sudoku data struct 
                return sudoku;
        }
}

/************** fill_square **************/
/* Fills 3x3 squares of the sudoku board, with x and y being the upper 
 * left coordinates of the square */
void fill_square(sudoku_t* sudo, int x, int y)
{
    int row = x;

    //filling the squares, three rows at a time
    while (row < x + 3) {
        int col = y;
        //filling the squares, three columns at a time 
        while (col < y + 3) {
            int num = rand() % 9 + 1; // generate random num and try to insert it

            //making sure that the random number generated for this square is valid
            //with regards to the square in which it is found 
            if (can_fit_square(sudo, row, col, num)){

                //if the value is valid, set the square to this value 
                sudo->board[row][col] = num;

                col++; // only move on if the num fits
            }
        }
        row++;
    }
}

/**************** fill_board() ***************/
/* same as solve, but generates a unique solution each time */
bool fill_board(sudoku_t* sudo) {
    //if the board is already full, return true         
    if (is_full(sudo)){
        return true;
    }

    //possible values for each square   
    int values[9] = {1,2,3,4,5,6,7,8,9};
    //shuffling the values so that they are randomized
    shuffle(values, 9);
    //looping over the columns  
    for (int x = 0; x < 9; x++){
        //looping over the rows
        for (int y = 0; y < 9; y++){
                //if the spot is empty
                if (sudo->board[x][y] == 0){
                        //looping over the values in the values list
                        for (int n = 0; n <= 8; n++) {
                                //if the value is valid for the row, column
                                //and square 
                                if (can_fit(sudo, x, y, values[n])) {
                                        //assign the value to this square
                                        sudo->board[x][y] = values[n];
                                        //if the board is full
                                        if (fill_board(sudo)){
                                                return true;
                        }
                        //setting empty space 
                        sudo->board[x][y] = 0;
                    }
                }
                return false;
            }
        }
    }
    return false;
}

/*************** remove_num() ************/
/* Removes a specified number of values from a sudoku board given the sudoku
 * board and a number of values to remove. */
void remove_num(sudoku_t* sudo, int num) {

    int i = 0;
    //while there are still values to remove
    while (i < num) {
        //generating random value for x coordinate to make empty 
        int x = rand() % 9;
        //generating random value for y coordinate to make empty 
        int y = rand() % 9;
        //if the spot is not already empty
        if (sudo->board[x][y] != 0) {
            //setting the spot equal to zero, signifying empty space
            sudo->board[x][y] = 0;
            // iterate i only if we changed a value
            i++;
        }
    }

    return;
}

/***************** print_board() ****************/
/* Prints the contents of the given sudoku table in a 9x9 format. */
void print_board(sudoku_t* sudo)
{
    //declaring integer variables
    int i,j;

    //looping through the columns
    for (i = 0; i < 9; i++) {
            //looping through the rows
            for(j = 0; j < 9; j++){
                    //printing the value associated with that square of the
                    //board
                    printf("%d ", sudo->board[i][j]);
        }
        //printing new line after each row 
        printf("\n");
    }
}

/************ is_full() **********/
/* Checks to see if the board is full. Returns true if full, false otherwise. */
bool is_full(sudoku_t* sudo){
    int i, j;
    //looping over columns
    for (i = 0; i < 9; i++){
        //looping over rows
        for (j = 0; j < 9; j++){
                //if there is a 0, the board is not full
                //as 0's correspond to empty squares on the board
                if (sudo->board[i][j] == 0){
                        return false;
            }
        }
    }
    //if there are no 0's, board is empty, return true 
    return true;
}

/************ can_fit() **********/
/* Checks to see that the given value, n, is valid with regards to the column, row, 
 * and the square in which the x, y square is found. */
bool can_fit(sudoku_t* sudo, int x, int y, int n){

    //calling each of the three helper functions to test each of the requirements 
    return can_fit_column(sudo, x, y, n) && can_fit_row(sudo, x, y, n) && can_fit_square(sudo, x, y, n);
}

/*************** can_fit_column() ***********/
/* Checking to see if the value is valid for the column. */
bool can_fit_column(sudoku_t* sudo, int x, int y, int n){
    //traversing over the column in which the square at coordinates
    //x, y is found 
    for (int i = 0; i < 9; i++) {
            //if this value is already in the column, return false 
            //because the same value cannot be found twice within a column
            if (sudo->board[x][i] == n){
                 return false;
        }
    }
    //if the value is not already in the column, return true 
    return true;
}

/************ can_fit_row() *************/
/* Checking to see if the value is valid for the row. */
bool can_fit_row(sudoku_t* sudo, int x, int y, int n){
    //traversing over the row in which the square at coordinates
    //x, y is found
    for (int i = 0; i < 9; i++){
            //if this value is already in the row, return false
            //because the same value cannot be found twice within a row
            if (sudo->board[i][y] == n){
                return false;
        }
    }
    //if the value is not already in the row, return true 
    return true;
}

/********** can_fit_square() *************/
/* Checks if a given value, n, is valid for the position at x, y in the 
 * sudoku board. */
bool can_fit_square(sudoku_t* sudo, int x, int y, int n)
{
    int xval = (x / 3) * 3;
    int yval = (y / 3) * 3;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (sudo->board[xval + i][yval + j] == n){
                return false;
            }
        }
    }
    return true;
}

/************ shuffle() ************/
/* Arrange the N elements of the array in a random order. */
void shuffle(int *array, size_t n){
    //nothing to shuffle if there is only one item in the array
    if (n > 1)
    {
        //variable to traverse the array 
        size_t i;

        //looping through the array
        for (i = 0; i < n - 1; i++)
        {
          //generating random integer value which is the index whose value
          //will be exchanged with the integer value in array[i]
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);

          //temporary variable to store the initial value in array[j]
          int t = array[j];

          //setting array[j] to the value in array[i] 
          array[j] = array[i];

          //setting the value in array[i] to the stored value from array[j], i 
          //is the randomly generated index 
          array[i] = t;
        }
    }
}

/**************** delete_sudoku() *************/
/* Frees the memory associated with the given sudoku data struct. 
 * Does nothing if the given sudoku data struct is NULL. */
void delete_sudoku(sudoku_t* sudo) 
{
	//as long as the given sudoku table is not NULL
	if (sudo != NULL) {
		
		//freeing the memory associated with given data
		//struct
		free(sudo); 
	}
	
	return; 
}


