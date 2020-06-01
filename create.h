/*
 * create.h - header file for CS50 create module
 *
 * A *create* is a module which holds one function which initializes the values
 * for a given sudoku data struct.
 *
 * Valgrinders, May 2020
 *
 */

#ifndef __CREATE_H
#define __CREATE_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

/**************** functions ***************/

/*************** create *************/
/* Initializes the values for a given sudoku data struct so that it is a valid
 * sudoku table. 
 *
 * Caller provides: 
 *      nothing
 * We return:
 *      a sudoku_t pointer
 * Caller is responsible for:
 *      later calling sudoku_delete in order to free the memory associated with
 *      the newly initialized sudoku*.
 */
sudoku_t* create();

#endif // __CREATE_H

