#Name: Valgrinders
#Date: May, 2020
#File name: testing.sh
#This program tests create.c, solve.c, and sudoku.c 

#!/bin/bash

#testing with too few arguments
./sudoku

#testing with too many arguments
./sudoku create solve

#calling create 
./sudoku create

#calling solve and inputting table of invalid size
./sudoku solve |  1 2 3 4 5 5 6 7 8 9 9
        	2 4 5 6 7 8 8 9 2 3 9
       		1 2 3 5 6 7 8 9 6 5 3
        	2 3 4 5 6 7 4 3 2 4 5
        	9 8 8 7 7 6 8 9 6 6 6
        	3   2 4   4 2   3   3
        	3     1     1   1   1
        	3 2 1 4     4   2   1
        	2 1 4 6 7 8 5 4 3 5 6

#calling solve and inputting completed table
./sudoku solve | 1 2 3 5 6 3 2 4 5
        	1 2 3 5 6 3 2 4 5
        	1 2 3 5 6 3 2 4 5
        	1 2 3 5 6 3 2 4 5
        	1 2 3 5 6 3 2 4 5
        	1 2 3 5 6 3 2 4 5
        	1 2 3 5 6 3 2 4 5
        	1 2 3 5 6 3 2 4 5
        	1 2 3 5 6 3 2 4 5

#calling solve and inputting table which is not full but is already invalid
./sudoku solve | 1 1 1 1 1 1 1 1 1
        	1 2   4   5   5 5
        	1   4   4   4 4 4
        	2 6 3 1 3 5 6 4 3
       		3 5 6 7 8 9 5 3 2
        	3 4 5 6 8 9 6 4 3
        	2 4 5 7 8 5 4   3
        	2 3     5   7   3
        	3 4 6 7   3 5   6 

#calling solve and sending in a table with very few values 
./sudoku solve | 1                2







        	2                 3

#calling solve and sending in non-integer values
./sudoku solve | a b c e d a c e a
        	 1 2 4 5 6 4 2 3 4
        	 3 2 4 5 6 4 3 2 4
        	 3 2 3 5 6 4 3 5 6
        	 3 2 4 5 6 4 3 3 5
        	 3 4 4 4 6 7 4 2 4
        	 3 4 5 6 4 3 4 5 3
        	 9 4 5 6 4 3 2 4 5
        	 4 5 6 4 2 3 4 5 4

#calling solve and giving a completely empty table
./sudoku solve | 0 0 0 0 0 0 0 0 0
        	0 0 0 0 0 0 0 0 0
        	0 0 0 0 0 0 0 0 0
        	0 0 0 0 0 0 0 0 0
        	0 0 0 0 0 0 0 0 0
        	0 0 0 0 0 0 0 0 0
        	0 0 0 0 0 0 0 0 0
        	0 0 0 0 0 0 0 0 0
        	0 0 0 0 0 0 0 0 0

#calling with invalid argument
./sudoku run


