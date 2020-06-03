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
cat testfile1 | ./sudoku solve 

#calling solve and inputting completed table
cat testfile2 | ./sudoku solve 

#calling solve and inputting table which is not full but is already invalid
cat testfile3 | ./sudoku solve 

#calling solve and sending in table with very few values
cat testfile4 | ./sudoku solve

#calling solve and sending in non-integer values
cat testfile5 | ./sudoku solve 

#calling solve and giving a completely empty table
cat testfile6 | ./sudoku solve 

#calling with invalid argument
./sudoku run

#testing solve better with table of invalid size 
cat testfile1 | ./sudoku better

#calling solve and inputting completed table
cat testfile2 | ./sudoku better

#calling solve and inputting table which is not full but is already invalid
cat testfile3 | ./sudoku better

#calling solve and sending in table with very few values
cat testfile4 | ./sudoku better

#calling solve and sending in non-integer values
cat testfile5 | ./sudoku better

#calling solve and giving a completely empty table
cat testfile6 | ./sudoku better
