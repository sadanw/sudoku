#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "sudoku.h"

/* Function headers */

void print_table(int table [9][9]);
bool can_fit(int x, int y, int n);
bool can_fit_column(int x, int y, int n);
bool can_fit_row(int x, int y, int n);
bool can_fit_square(int x, int y, int n);
bool solve();
void create();
bool read_table(FILE *fp);
bool is_full(int table [9][9]);

/* Global variables */

int arr[9][9] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
        };
int empty[9][9];

/*
TODO: Maybe make a struct that will hold our 2D array?
This will make it easier to return from methods
because you can't easily return 2D arrays from methods
*/
typedef struct sudoku{
    int board[9][9];
} sudoku_t;

int main(int argc, char *argv[]){
    if (argc != 2){
        fprintf(stderr, "Incorrect number of parameters\nUsage: \nsudoku create\nor\nsudoku solve\n");
        return 0;
    }

    if (strcmp("create", argv[1]) == 0) {
        printf("create:\n");

        FILE* fp = fopen("exampleSudoku", "r");
        read_table(fp);
        fclose(fp);

        printf("table:\n");
        print_table(empty);
        printf("\n");
    }

    else if (strcmp("solve", argv[1]) == 0) {
        
    }

    else {
        fprintf(stderr, "Usage: \nsudoku create\nor\nsudoku solve\n");
        return 1;
    }
    // could probably delete
    //print_table(arr);

    //solve();
    // print_table(arr);

    // read_table(stdin);
    // printf("table:\n");
    // print_table(empty);
    // printf("\n");

    return 0;
}

bool solve(){
    if (is_full(arr)){
        return true;
    }

    for (int x = 0; x < 9; x++){
        for (int y = 0; y < 9; y++){
            if (arr[x][y] == 0){
                for (int n = 1; n <= 9; n++) { 
                    if (can_fit(x, y, n)) { 
                        arr[x][y] = n; 
                        if (solve()){
                            return true;
                        }
                        arr[x][y] = 0; 
                    } 
                } 
                return false; 
            }
        }
    }
    return false;
}

void print_table(int table [9][9]){
    int i,j;
    for(i = 0; i < 9; i++){
        for(j = 0; j < 9; j++){
            printf("%d ", table[i][j]);
        }
        printf("\n");
    }
}

bool read_table(FILE *fp){
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            int d;
            if (fscanf(fp, "%d ", &d) != 1){
                fprintf(stderr, "invalid value");
                return false;
            }
            else{
                empty[i][j] = d;
            }
        }
    }
    return true;
}

bool can_fit_column(int x, int y, int n){
    for (int i = 0; i < 9; i++) {
        if (arr[x][i] == n){
            return false;
        }
    }
    return true;
}

bool can_fit_row(int x, int y, int n){
    for(int i = 0; i < 9; i++){
        if (arr[i][y] == n){
            return false; 
        }
    }
    return true;
}

bool can_fit_square(int x, int y, int n){
    int xval = (x / 3) * 3;
    int yval = (y / 3) * 3;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (arr[xval + i][yval + j] == n){
                return false;
            }
        }
    }
    return true;
}

bool can_fit(int x, int y, int n){
    return can_fit_column(x, y, n) && can_fit_row(x, y, n) && can_fit_square(x, y, n);
}

bool is_full(int table [9][9]){
    int i,j;
    for(i = 0; i < 9; i++){
        for(j = 0; j < 9; j++){
            if (table[i][j] == 0){
                return false;
            }
        }
    }
    return true;
}