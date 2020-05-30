#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "sudoku.h"
#include "create.h"
#include "solve.h"

/* Global types */

typedef struct sudoku{
    int board[9][9];
} sudoku_t;

/* Function headers */
sudoku_t* create();
void fill_square(sudoku_t* sudo, int x, int y);
bool fill_board(sudoku_t* sudo);
void remove_num(sudoku_t* sudo, int num);
bool solve(sudoku_t* sudo);
sudoku_t* load_board(FILE *fp);
bool is_full(sudoku_t* sudo);
bool can_fit(sudoku_t* sudo, int x, int y, int n);
bool can_fit_column(sudoku_t* sudo, int x, int y, int n);
bool can_fit_row(sudoku_t* sudo, int x, int y, int n);
bool can_fit_square(sudoku_t* sudo, int x, int y, int n);
void shuffle(int *array, size_t n);
int testfunc();

/*
TODO: in create(), make sure that the board it creates has a unique solution
*/

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
        free(new);
    }

    else if (strcmp("solve", argv[1]) == 0) {
        sudoku_t* new = load_board(stdin);
        solve(new);
        printf("solved:\n");
        print_board(new);
        free(new);
    }

    else {
        fprintf(stderr, "Usage: \nsudoku create\nor\nsudoku solve\n");
        return 1;
    }

    return 0;
}

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

/* x, y pair is upper left coordinate of square */
void fill_square(sudoku_t* sudo, int x, int y) {
    int row = x;
    while (row < x + 3) {
        int col = y;
        while (col < y + 3) {
            int num = rand() % 9 + 1; // generate random num and try to insert it
            if (can_fit_square(sudo, row, col, num)){
                sudo->board[row][col] = num;
                col++; // only move on if the num fits
            }
        }
        row++;
    }
}

/* same as solve, but generates a unique solution each time */
bool fill_board(sudoku_t* sudo) {

    if (is_full(sudo)){
        return true;
    }

    int values[9] = {1,2,3,4,5,6,7,8,9};
    shuffle(values, 9);

    for (int x = 0; x < 9; x++){
        for (int y = 0; y < 9; y++){
            if (sudo->board[x][y] == 0){
                for (int n = 0; n <= 8; n++) { 
                    if (can_fit(sudo, x, y, values[n])) { 
                        sudo->board[x][y] = values[n]; 
                        if (fill_board(sudo)){
                            return true;
                        }
                        sudo->board[x][y] = 0; 
                    } 
                } 
                return false; 
            }
        }
    }
    return false;
}

void remove_num(sudoku_t* sudo, int num) {
    int i = 0;
    while (i < num) {
        int x = rand() % 9;
        int y = rand() % 9;
        if (sudo->board[x][y] != 0) {
            sudo->board[x][y] = 0;
            i++; // iterate i only if we changed a value
            
        }
    }

    return;
}

bool solve(sudoku_t* sudo){
    if (is_full(sudo)){
        return true;
    }


    for (int x = 0; x < 9; x++){
        for (int y = 0; y < 9; y++){
            if (sudo->board[x][y] == 0){
                for (int n = 1; n <= 9; n++) { 
                    if (can_fit(sudo, x, y, n)) { 
                        sudo->board[x][y] = n; 
                        if (solve(sudo)){
                            return true;
                        }
                        sudo->board[x][y] = 0; 
                    } 
                } 
                return false; 
            }
        }
    }
    return false;
}

void print_board(sudoku_t* sudo){
    int i,j;
    for(i = 0; i < 9; i++){
        for(j = 0; j < 9; j++){
            printf("%d ", sudo->board[i][j]);
        }
        printf("\n");
    }
}

sudoku_t* load_board(FILE *fp){
    sudoku_t* new = malloc(sizeof(sudoku_t));
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

bool is_full(sudoku_t* sudo){
    int i,j;
    for(i = 0; i < 9; i++){
        for(j = 0; j < 9; j++){
            if (sudo->board[i][j] == 0){
                return false;
            }
        }
    }
    return true;
}

bool can_fit(sudoku_t* sudo, int x, int y, int n){
    return can_fit_column(sudo, x, y, n) && can_fit_row(sudo, x, y, n) && can_fit_square(sudo, x, y, n);
}

bool can_fit_column(sudoku_t* sudo, int x, int y, int n){
    for (int i = 0; i < 9; i++) {
        if (sudo->board[x][i] == n){
            return false;
        }
    }
    return true;
}

bool can_fit_row(sudoku_t* sudo, int x, int y, int n){
    for(int i = 0; i < 9; i++){
        if (sudo->board[i][y] == n){
            return false; 
        }
    }
    return true;
}

bool can_fit_square(sudoku_t* sudo, int x, int y, int n){
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

void shuffle(int *array, size_t n){
    if (n > 1) 
    {
        size_t i;
        for (i = 0; i < n - 1; i++) 
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
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