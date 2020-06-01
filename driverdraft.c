#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "sudokudraft.h"
#include "create.h"
#include "solve.h"

//main function- checks that the command line arguments are correct
//if command line argument is create, creates a new sudoku data struct and calls
//create function from create module on it
//if command line argument is solve, uses user given sudoku table to make a new
//data struct and then calls solve function in solve module on it 
int main(int argc, char *argv[]){

    //checking that the correct number of arguments was given, returning
    //error otherwise
    if (argc != 2){
        fprintf(stderr, "Error: Incorrect number of parameters\nUsage: \nsudoku create\nor\nsudoku solve\n");
        return 1;
    }

    // if user calls create, makes a sudoku data struct and prints it to stdout,
    // board can then be piped into ./sudoku solve
    if (strcmp("create", argv[1]) == 0) {
            //declaring and initializing a new sudoku data struct
            sudoku_t *new = sudoku_new();

            //calling create function in create module to fill the table
            //with valid values
            create(new);

            //calling sudoku module function, print_board to print the table
            print_board(new);

            //freeing the memory associated with the sudoku data struct
            //by calling sudoku module function, delete_sudoku
            delete_sudoku(new);
    }
    //if user calls solve, makes a sudoku data struct, solves it by calling
    //solve function in solve module, then prints the board 
    else if (strcmp("solve", argv[1]) == 0) {
	//declaring and initializing a new sudoku data struct using load_board
	//function in sudoku module 
        sudoku_t* new = load_board(stdin);
	
	//calling solve function in solve module to fill in the empty spaces
	//with valid values
        solve(new);

	//printing the board 
        printf("solved:\n");
        print_board(new);

	//freeing the memory associated with the sudoku data struct 
	//by calling sudoku module function, delete_sudoku
        delete_sudoku(new);
    }
	
    //if the user enters a command that is not create or solve,
    //it is not a valid command, exit with error code 
    else {
        fprintf(stderr, "Error: Usage: \nsudoku create\nor\nsudoku solve\n");
        return 2;
    }
	
    //return 0 if no errors 
    return 0;

}


