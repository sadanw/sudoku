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
#include "solve.c"
#include "create.c"

/****************** file-local global variables **************/
/* none */

/******************** local types **************/
// typedef struct square{
//         int value;      //value the square holds
//         int options[9]; //list of potential integers that could be the value
// } square_t;

/***************** global types ****************/
typedef struct sudoku{
    int board[9][9];    //2D array of all of the squares in the board
    // int options[9][9][9];
} sudoku_t;

/************* global functions *************/
/* visible outside this file */
/* see sodoku.h for comments about exported functions */

/***************** local functions **************/
/* not visible outside this file */

int main(int argc, char *argv[]){
    #ifdef MYTEST
    testfunc();
    #endif
    
    if (argc != 2){
        fprintf(stderr, "Incorrect number of parameters\nUsage: \nsudoku create\nor\nsudoku solve\n");
        return 0;
    }

    // makes a new board and prints it to stdout, can then be piped into ./sudoku solve
    if (strcmp("create", argv[1]) == 0) {        
        sudoku_t* new = create();
        print_board(new);
        sudoku_delete(new);
    }

    else if (strcmp("solve", argv[1]) == 0) {
        sudoku_t* new = load_board(stdin);
        solve(new);
        printf("solved:\n");
        print_board(new);
        sudoku_delete(new);
    }

    else {
        fprintf(stderr, "Usage: \nsudoku create\nor\nsudoku solve\n");
        return 1;
    }

    return 0;
}

// sudoku_t* create() {
//     sudoku_t* new = malloc(sizeof(sudoku_t));
    
//     if (new == NULL) {
//         return NULL;
//     }

//     // fill in diagonals
//     srand(time(NULL)); // use the time as a seed for rand()
//     fill_square(new, 0, 0);
//     fill_square(new, 3, 3);
//     fill_square(new, 6, 6);

//     // fill in remaining squares
//     fill_board(new);

//     // remove values
//     remove_num(new, 40);


//     // checking for unique solution here
//     sudoku_t* check = malloc(sizeof(sudoku_t));
//     for (int i = 0; i < 9; i++){
//         for (int j = 0; j < 9; j++){
//             check->board[i][j] = new->board[i][j];
//         }
//     }
    
//     // if more than one solution, try again
//     if (uni_solve(check, 0) > 1){
//         free(check);
//         return create();
//     }

//     free(check);

//     // return created board
//     return new;

// }

/******************* sudoku_new() **************/
/* Create a new (empty) sudoku. Returns pointer to new sodoku, or NULL if 
 * error. */
sudoku_t *sudoku_new(void)
{
        //allocating memory for the sodoku data struct
        sudoku_t *sudoku = malloc(sizeof(sudoku_t));

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

// bool solve(sudoku_t* sudo){
//     if (is_full(sudo)){
//         return true;
//     }


//     for (int x = 0; x < 9; x++){
//         for (int y = 0; y < 9; y++){
//             if (sudo->board[x][y] == 0){
//                 for (int n = 1; n <= 9; n++) { 
//                     if (can_fit(sudo, x, y, n)) { 
//                         sudo->board[x][y] = n; 
//                         if (solve(sudo)){
//                             return true;
//                         }
//                         sudo->board[x][y] = 0; 
//                     } 
//                 } 
//                 return false; 
//             }
//         }
//     }
//     return false;
// }

// // check for unique solution
// int uni_solve(sudoku_t* sudo, int sol){
//     if (is_full(sudo)){
//         sol += 1;
//         return sol;
//     }


//     for (int x = 0; x < 9; x++){
//         for (int y = 0; y < 9; y++){
//             if (sudo->board[x][y] == 0){
//                 for (int n = 1; n <= 9; n++) { 
//                     if (can_fit(sudo, x, y, n)) { 
//                         sudo->board[x][y] = n; 
//                         sol = uni_solve(sudo, sol);
//                         sudo->board[x][y] = 0; 
//                     } 

//                     if (sol > 1){
//                         return sol;
//                     }
//                 } 
//                 return sol; 
//             }
//         }
//     }
//     return sol;
// }

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

sudoku_t* load_board(FILE *fp){
    sudoku_t* new = sudoku_new();
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            int d;
            if (fscanf(fp, "%d ", &d) != 1){
                fprintf(stderr, "invalid value");
                return NULL;
            }
            else{
                new->board[i][j] = d;
            }
        }
    }
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

void copy_sudoku(sudoku_t* sudo, sudoku_t* copy) {
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            copy->board[i][j] = sudo->board[i][j];
        }
    }
}

/***************** compare_boards *****************
 * caller provides two sudoku structures
 * returns false if any non-zero numbers differ, true otherwise
 */
bool compare_boards(sudoku_t* sudo1, sudoku_t* sudo2) {
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            if ((sudo1->board[i][j] != 0) && (sudo2->board[i][j] != 0)) {
                if ((sudo1->board[i][j]) != (sudo2->board[i][j])) {
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
            if (!can_fit(sudo, i, j, sudo->board[i][j])) {
                return false;
            }
        }
    }
    return true;
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

int testfunc(){
    sudoku_t* sudobf = malloc(sizeof(sudoku_t));
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
