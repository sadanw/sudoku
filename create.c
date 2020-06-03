/* 
 * create.c - CS50 'create' module
 *
 * see create.h for more information
 *
 * Valgrinders, May 2020
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "sudoku.h"
#include "create.h"
#include "solve.h"

/********** create **********/
/* Creates a fully formed sudoku puzzle. Returns NULL if error. 
 * User is responsible for freeing the sudoku struct later or calling
 * sudoku_delete(). */
sudoku_t* create() {
    sudoku_t* new = sudoku_new();

    //if new sudoku data struct is NULL,
    //return NULL
    if (new == NULL) {
        return NULL;
    }

    //uses the computer's internal clock to control the choice of the seed,
    //since time continuously changes, the seed changes
    //using the time as a seed for rand() function
    srand(time(NULL));

    //calling sudoku module function, fill_square, on the squares of the board
    //forming a diagonal from the top left corner to the bottom right corner
    fill_square(new, 0, 0);
    fill_square(new, 3, 3);
    fill_square(new, 6, 6);

    // fill in remaining squares by calling the fill_board function in the 
    // sudoku module 
    fill_board(new);

    // calling the remove_num function in the sudoku module which removes
    // 40 values from the table while still maintaining a single solution
    // for the board
    remove_num(new, 40);

    // checking for unique solution here
    sudoku_t* check = sudoku_new();

    copy_sudoku(new, check);
    
    if (uni_solve(check, 0) > 1){
        delete_sudoku(check);
        delete_sudoku(new);
        return create();
    }

    delete_sudoku(check);

    // return created board
    return new;
}

