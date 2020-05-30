#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sudoku.h>
#include <create.h>
#include <solve.h>



sudoku_t* create() {
    sudoku_t* new = malloc(sizeof(sudoku_t));
    
    if (new == NULL) {
        return NULL;
    }

    // fill in diagonals
    srand(time(NULL)); // use the time as a seed for rand()
    fill_square(new, 0, 0);
    fill_square(new, 3, 3);
    fill_square(new, 6, 6);

    // fill in remaining squares
    fill_board(new);

    // remove values
    remove_num(new, 40);

    return new;

}