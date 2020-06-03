# Sudoku
## Lucas Boebel, Hailey Fox, Scott Gibbons, Sada Nichols-Worley
## CS50 Spring 2020

/* See Makefile for more details */
# Compiling:
```
        make
```

# Usage:
```
/*
 * sudoku.c - file is compiled into machine code and is put into sudoku file
 *
 * usage: play the sudoku game. Sudoku is a well known logic puzzle where
 *        numbers between 1 and 9 are placed on a 9x9 grid of cells. The
 *        placement of numbers follows a specific set of rules in which
 *        no number can be repeated within the same column, row, or set of 3x
 *        squares.
 * where:
 *      user must enter one argument: either create or solve.
 * output:
 *      when the user calls create, the program creates a randomly generated,
 *      but valid sudoku table and prints it to stdout. When the user calls
 *      solve, the program takes in the board created by the user in stdin. If *      there are missing spots in the table, solves the table, if it has a
 *      valid solution, and outputs the completed table to the user. If the
 *      table was full to begin with, the original table is printed to the
 *      user. If the table was unable to be solved, a message is printed
 *      saying that the table did not have a valid solution.
 * stdin: 1 argument
 * stdout: the sudoku table
 * stderr: error messages
 *
 * Valgrinders, May 2020
 */
```
# Example command lines:
```
        ./sudoku create
        ./sudoku solve
```
# Exit status:
```
        0 - no error
        1 - incorrect number of arguments give
        2 - board given by user did not have a valid solution
        3 - user entered a command line argument that was not create or solve
```
# Assumptions:
```
        - assuming the user does not enter a table that has more values
          than a 9x9 table
```
# Limitations:
```
        - the program assumes that the user only enters characters in the
          command line arguments
```

