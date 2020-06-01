/*
 * solve.h - header file for CS50 solve module
 *
 * A *solve* is a module which holds one function which takes a sudoku data 
 * struct and finds valid values for the empty spaces- denoted by 0's- and then
 * outputs the solved/completed table. 
 *
 * Valgrinders, May 2020
 *
 */

#ifndef __SOLVE_H
#define __SOLVE_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "sudoku.h"

/**************** functions ***************/

/************** solve ***************/
/* Fills in the empty spaces in the given sudoku data struct.
 *
 * Caller provides: 
 *      valid pointer to a sudoku data struct.
 * We return:
 *      true if the given sudoku struct was solvable, false otherwise.
 *      The solved/completed sudoku table is printed to stdout. The 
 *      given sudoku struct is now filled with valid values.
 * Caller is responsible for:
 *      later freeing the memory associated with the given sudoku data struct
 *      by calling the sudoku_delete function from the sudoku module.
 */
bool solve(sudoku_t *sudo);

#endif // __SOLVE_H

