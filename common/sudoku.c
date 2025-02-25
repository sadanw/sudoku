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

/***************** global types ****************/
typedef struct sudoku{
    int board[9][9];    //2D array of all of the squares in the board
} sudoku_t;


/************* global functions *************/
/* visible outside this file */
/* see sodoku.h for comments about exported functions */

/***************** local functions **************/
/* not visible outside this file */

//Main function to parse command line arguments, assure their validity, and 
//call either the create, solve modules depending on the user's arguments

/******************* sudoku_new() **************/
/* Create a new (empty) sudoku. Returns pointer to new sodoku, or NULL if 
 * error. */
sudoku_t *sudoku_new(void)
{
        //allocating memory for the sodoku data struct
        sudoku_t *sudoku = calloc(1, sizeof(sudoku_t));

        //returning NULL if there is an error creating the sodoku
        if (sudoku == NULL) {
            return NULL;
        }

        //otherwise return pointer to new sodoku struct
        else {
            //returning pointer to sudoku data struct 
            return sudoku;
        }
}

/************** fill_square **************/
/* Fills 3x3 squares of the sudoku board, with x and y being the upper 
 * left coordinates of the square */
void fill_square(sudoku_t* sudo, int x, int y)
{
    int row = x;
    int col = y;

    //creating list of potential values that can be in the table
    int values[9] = {1,2,3,4,5,6,7,8,9};
    //shuffling values within the index so the values are randomly added to 
    //the table if valid
    shuffle(values, 9);

    //filling the squares, three rows at a time
    while (row < x + 3) {
        //filling the squares, three columns at a time 
        while (col < y + 3) {
            for (int n = 0; n <= 8; n++) {

                //making sure that the random number generated for this square is valid
                //with regards to the square in which it is found 
                if (can_fit(sudo, row, col, values[n])){

                    //if the value is valid, set the square to this value 
                    sudo->board[x][y] = values[n];
                    col++; // only move on if the num fits
                }
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

/***************** load_board() *************/
/* Loads the contents in a file or from stdin into a valid Sudoku data 
 * struct. */ 
sudoku_t* load_board(FILE *fp){
    //creating new sudoku data struct
    sudoku_t* new = sudoku_new();
	
    //looping over the columns in the table
    for (int i = 0; i < 9; i++){
	//looping over the rows in the table
        for (int j = 0; j < 9; j++){
	   
            int d;
            //scanning the values in from the file 
            if (fscanf(fp, " %d", &d) != 1){
		//if a value is not an integer, print error message
		//and stop loading the table
                fprintf(stderr, "Error: Invalid value.\n");
                return NULL;
            }
            
	    //if the value read in is valid, set the corresponding square
	    //in the table to this value 
            else{
                new->board[i][j] = d;
            }
        }
    }
    //return pointer to newly created data struct 
    return new;
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
            if (sudo->board[xval + i][yval + j] == n){
                return false;
            }
        }
    }
    return true;
}

/************* bettersolve ************/
/* Creating a more efficient solve function. */
bool bettersolve(sudoku_t* sudo){
    //no need to solve the table if it is already full
    if (is_full(sudo)){
        return true;
    }
    //looping over the columns in the table
    for (int x = 0; x < 9; x++){
	//looping over the rows in the table
        for (int y = 0; y < 9; y++){
	    //if the current square in the board is empty
            if (sudo->board[x][y] == 0){
		//creating new array to determine which values are valid
                int vals [9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
		//calling better_fit helper function to determine 
		//which values are valid 
                better_fit(sudo, vals, x, y);
		//looping over list which was edited by better_fit
                for (int i = 0; i < 9; i++) { 
		    //if the value in a particular index is 1
                    if (vals[i] == 1) { 
			//use the index of this value+1, to account for the 
			//index starting at 0, as the value in the particular
			//square of the board
                        sudo->board[x][y] = i+1;
		        //if the table is full, can stop looking for empty 
			//spaces and return true 	
                        if (bettersolve(sudo)){
                            return true;
                        }
			//if there are still more spaces to be found, set 
			//current square as an empty space 
                        sudo->board[x][y] = 0; 
                    } 
                } 
		
                return false; 
            }
        }
    }
    return false;
}


/************* better_fit *************/

/* For the x and y value given, it will update possible_vals 
 * so that a 0 means that value cannot be placed, and a 1 means that it can
 *NOTE: a value of 1 is associated with index 0 (not 1). */
void better_fit(sudoku_t* sudo, int possible_vals[9], int x, int y){
    //looping through the potential values that can be in table, 1-9
    for (int n = 1; n <= 9; n++){
        // check columns
        for (int i = 0; i < 9; i++) {
	    //if the value is already in this row then set the corresponding 
	    //index of n-1 value to 0 signify that this value is not valid
            if (sudo->board[x][i] == n){
                possible_vals[n-1] = 0;
            }
        }
        // check rows
        for(int i = 0; i < 9; i++){
            if (sudo->board[i][y] == n){
                possible_vals[n-1] = 0;
            }
        }
        // check square
        int xval = (x / 3) * 3;
        int yval = (y / 3) * 3;
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                if (sudo->board[xval + i][yval + j] == n){
                    possible_vals[n-1] = 0;
                }
            }
        }
    }
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

/************** get_value ***************/
/* Getter function to retrieve the value associated with the square with 
 * coordinates x, y. */
int get_value(sudoku_t* sudo, int x, int y) {
    	//return particular value
	return sudo->board[x][y];
}

/************* set_value **************/
/* Setter function to set the value for the square with coordinates x, y. */
void set_value(sudoku_t* sudo, int x, int y, int n) {
    //updating this value
    sudo->board[x][y] = n;
}

/************ copy_sudoku *************/
/* Copying the contents of the first sudoku table into the second table. */
void copy_sudoku(sudoku_t* sudo, sudoku_t* copy) {
    //looping through the columns of the first table
    for (int i = 0; i < 9; i++){
	//looping through the rows of the second table
        for (int j = 0; j < 9; j++){
	    //setting the value in the new table for current square as 
	    //corresponding value in original table
            copy->board[i][j] = sudo->board[i][j];
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
		//freeing the memory associated with given data struct
		free(sudo); 
	}
	
}


#ifdef MYTEST
int fullgrid[9][9] = {
{1, 2, 5, 6, 7, 9, 8, 3, 5},
{1, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 1, 1, 1, 1, 1, 1, 1, 1},
};

int partialgrid[9][9] = {
{0, 0, 0, 0, 6, 5, 2, 0, 0},
{6, 0, 5, 0, 0, 2, 0, 7, 3},
{2, 0, 0, 3, 0, 0, 6, 0, 4},
{0, 0, 0, 0, 5, 0, 8, 0, 0},
{8, 2, 7, 0, 4, 0, 5, 1, 9},
{0, 0, 3, 0, 7, 0, 0, 0, 0},
{9, 0, 2, 0, 0, 6, 0, 0, 5},
{7, 6, 0, 5, 0, 0, 3, 0, 8},
{0, 0, 1, 8, 2, 0, 0, 0, 0},
};

/************ testfunc ************/
/* Function which performs Macros testing on the program. */
int testfunc(){
    sudoku_t* sudobf = sudoku_new();
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            sudobf->board[i][j] = fullgrid[i][j];
        }
    }
    fprintf(stdout, "%d\n", is_full(sudobf));

    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            sudobf->board[i][j] = partialgrid[i][j];
        }
    }
    fprintf(stdout, "%d\n", is_full(sudobf));

    fprintf(stdout, "%d\n", can_fit_row(sudobf, 0, 0, 4));
    fprintf(stdout, "%d\n", can_fit_row(sudobf, 4, 4, 4));
    fprintf(stdout, "%d\n", can_fit_column(sudobf, 5, 1, 6));
    fprintf(stdout, "%d\n", can_fit_square(sudobf, 0, 0, 5));

    fprintf(stdout, "%d\n", can_fit(sudobf, 0, 0, 1));
    fprintf(stdout, "%d\n", can_fit(sudobf, 6, 1, 5));

    sudoku_t *sudocr = create();
    print_board(sudocr);

    fprintf(stdout, "-- -- -- --\n");
    
    solve(sudocr);
    print_board(sudocr);


    return 0;
}


#endif
