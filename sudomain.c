#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "common/sudoku.h"
#include "common/solve.h"
#include "common/create.h"


int main(int argc, char *argv[]){
    #ifdef MYTEST
        testfunc();
    #endif
    
    //checking that the correct number of command line arguments was given
    if (argc != 2){
        fprintf(stderr, "Error: User must give one argument.\n");
        return 1; 
    }

    // makes a new board and prints it to stdout, can then be piped into ./sudoku solve
    if (strcmp("create", argv[1]) == 0) {        
	//creating new data structure by calling create module function
        sudoku_t* new = create();
	
	//making sure table generated by create is not NULL
	if (new == NULL) {
		fprintf(stderr, "Error: create could not generate table.\n"); 
		return 2; 
	} 

	//printing table to standard out and freeing memory associated with table
      
        print_board(new);
        delete_sudoku(new);
    }
	
    //if user calls solve, the function in solve module is called 
    else if (strcmp("solve", argv[1]) == 0) {
	//creating new data structure by loading in the table given by stdin
        sudoku_t* new = load_board(stdin);
	//if the new table is NULL return with error code
        if (new == NULL) {
		fprintf(stderr, "Error: table is not solvable.\n");
		return 3;
	}
	//calling solve function on new sudoku table 
        solve(new);
        printf("solved:\n");
	//printing sudoku board
        print_board(new);

	//deleting memory associated with sudoku table 
        delete_sudoku(new);
    }
    //if the better argument is given, call bettersolve 
    else if (strcmp("better", argv[1]) == 0) {
	//loading info from stdin into new sudoku data struct
        sudoku_t* new = load_board(stdin);
	//if the loaded table is NULL, return with error code
        if (new == NULL) {
	        fprintf(stderr, "Error: load_board gave NULL table.\n"); 	
		return 4;
	}
		//calling better solve function to fill in empty spaces in table
        bettersolve(new);
        printf("solved:\n");
	//printing the board and freeing the data associated with the table 
        print_board(new);
        free(new);
    }
    //if the user did not call create, solve, or better, then the command
    //is invalid, return with error code 
    else {
        fprintf(stderr, "Error: Usage: \nsudoku create\nor\nsudoku solve\nor\nsudoku better\n");
        return 5;
    }

    return 0;
}
