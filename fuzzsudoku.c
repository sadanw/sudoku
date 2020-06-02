/*
 * fuzzsudoku.c - a program to perform fuzztesting of our sudoku creator/solver
 * Valgrinders, May 2020
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>

#include "solve.h"
#include "create.h"
#include "sudoku.h"

/* Function headers */
bool isPositiveNumber(char number[]);

int main(const int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: ./fuzzsudoku numTest\n");
        return 1;
    }

    if (!isPositiveNumber(argv[1])) {
        fprintf(stderr, "Usage: ./fuzzsudoku numTest\n");
        return 1;
    }

    else {
        int numTest = atoi(argv[1]);
        for (int i = 0; i < numTest; i++) {
            sudoku_t* new = sudoku_new();
            int numSolutions = 0;

            printf("--------------------------------------------------");
            printf("Generated board #%d: \n", i);
            print_board(new);

            // make a copy of the new board
            sudoku_t* copy = sudoku_new();
            copy_sudoku(new, copy);

            // solve the board and ensure it is unique
            numSolutions = uni_solve(new, 0);

            printf("Solved board #%d: \n", i);
            print_board(new);

            if (numSolutions == 0) {
                printf("Created board has no solution.\n");
            }
            else if (numSolutions > 1) {
                printf("Created board has %d solutions.\n", numSolutions);
            }
            else {
                printf("Created board has %d solution.\n", numSolutions);
            }

            // check board follows sudoku rules
            if (!isValidSolution(new)) {
                printf("Solution is not valid.\n");
            }
            else {
                printf("Solution is valid.\n");
            }

            // check the solver did not modify original values in board
            if (!compare_boards(new, copy)) {
                printf("Solving the sudoku modified the original values in the board.\n");
            }
            else {
                printf("Solving the sudoku did not modify the original values in the board.\n");
            }

            // clean up
            if (new != NULL) {
                delete_sudoku(new);
            }

            if (copy != NULL) {
                delete_sudoku(copy);
            }
        }
    }
    return 0;
}

/***************** isPositiveNumber *****************
 * takes a char[], returns whether or not it can be converted to an int
 * modified from: https://stackoverflow.com/a/29248688
 */
bool isPositiveNumber(char number[]) {
    int i = 0;

    //checking for negative numbers
    if (number[0] == '-') {
        return false;
    }
    for (; number[i] != 0; i++)
    {
        //if (number[i] > '9' || number[i] < '0')
        if (!isdigit(number[i])) {
            return false;
        }
    }
    return true;
}
