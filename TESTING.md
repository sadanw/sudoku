TESTING for sudoku.c
Valgrinders, May 2020

# A. entering too few command line arguments
```
./sudoku 

prints:
	Error: User must give one argument.
./sudoku

prints:
        Error: User must give one argument.
exit code = 1 (not printed)
```

# B. entering too many command line arguments
```
./sudoku create solve 

prints:
	Error: User must give one argument. 
exit code = 1 (not printed)
```

# C. calling create in command line 
```
./sudoku create

prints: 
	sudoku table which has 40 missing values, displayed as 0's, and 
	which has one unique solution
exit code = 0 (not printed) 
```

# D. calling solve in command line and piping in the contents of a file holding sudoku with invalid size
```
cat testfile1 | ./sudoku solve

testfile1: 
	1 2 3 4 5 5 6 7 8 9 9
	2 4 5 6 7 8 8 9 2 3 9 
	1 2 3 5 6 7 8 9 6 5 3
	2 3 4 5 6 7 4 3 2 4 5 
	9 8 8 7 7 6 8 9 6 6 6
	3   2 4   4 2   3   3
	3     1     1   1   1
	3 2 1 4     4   2   1 
	2 1 4 6 7 8 5 4 3 5 6 

prints:

	solved:
	1 2 3 4 5 5 6 7 8 
	9 9 2 4 5 6 7 8 8 
	9 2 3 9 1 2 3 5 6 
	7 8 9 6 5 3 2 3 4 
	5 6 7 4 3 2 4 5 9 
	8 8 7 7 6 8 9 6 6 
	6 3 2 4 4 2 3 3 3 
	1 1 1 1 3 2 1 4 4 
	2 1 2 1 4 6 7 8 5 
exit code = 0 (not printed)
```

# E. calling solve and sending in fully completed table by piping in file
```
cat tesfile2 | ./sudoku solve

testfile2: 
	1 2 3 5 6 3 2 4 5 
	1 2 3 5 6 3 2 4 5
	1 2 3 5 6 3 2 4 5
	1 2 3 5 6 3 2 4 5
	1 2 3 5 6 3 2 4 5
	1 2 3 5 6 3 2 4 5
	1 2 3 5 6 3 2 4 5
	1 2 3 5 6 3 2 4 5
	1 2 3 5 6 3 2 4 5

prints:
	solved: 
	1 2 3 5 6 3 2 4 5
	1 2 3 5 6 3 2 4 5
	1 2 3 5 6 3 2 4 5
	1 2 3 5 6 3 2 4 5
	1 2 3 5 6 3 2 4 5
	1 2 3 5 6 3 2 4 5
	1 2 3 5 6 3 2 4 5
	1 2 3 5 6 3 2 4 5
	1 2 3 5 6 3 2 4 5
exit code = 0 (not printed)
```

# F. calling solve and sending in table which not full and is invalid by piping in file 
```
cat testfile3 | ./sudoku solve 

testfile3:
	1 1 1 1 1 1 1 1 1 
	1 2 0 4 0 5 0 5 5
	1 0 4 0 4 0 4 4 4 
	2 6 3 1 3 5 6 4 3 
	3 5 6 7 8 9 5 3 2 
	3 4 5 6 8 9 6 4 3 
	2 4 5 7 8 5 4 0 3
	2 3 0 0 5 0 7 0 3
	3 4 6 7 0 3 5 0 6 

prints:
	solved:
	1 1 1 1 1 1 1 1 1 
	1 2 0 4 0 5 0 5 5 
	1 0 4 0 0 4 0 4 4 
	2 6 3 1 3 5 6 4 3 
	3 5 6 7 8 9 5 3 2 
	3 4 5 6 8 9 6 4 3 
	2 4 5 7 8 5 4 0 3 
	2 3 0 0 5 0 7 0 3 
	3 4 6 7 0 3 5 0 6 
exit code = 0 (not printed)	
```

# G. calling solve and sending in a table with very few values by piping in file
```
cat testfile4 | ./sudoku solve

testfile4:
	1 0 0 0 0 0 0 0 2
	0 0 0 0 0 0 0 0 0
	0 0 0 0 0 0 0 0 0
	0 0 0 0 0 0 0 0 0
	0 0 0 0 0 0 0 0 0
	0 0 0 0 0 0 0 0 0
	0 0 0 0 0 0 0 0 0
	0 0 0 0 0 0 0 0 0
	2 0 0 0 0 0 0 0 3	

prints:
	solved:
	1 3 4 5 6 7 8 9 2 
	5 2 6 1 8 9 3 4 7 
	7 8 9 2 3 4 1 5 6 
	3 1 2 4 5 6 7 8 9 
	4 5 7 3 9 8 2 6 1 
	6 9 8 7 1 2 4 3 5 
	8 7 3 9 2 5 6 1 4 
	9 4 1 6 7 3 5 2 8 
	2 6 5 8 4 1 9 7 3 
exit code = 0 (not printed)	
```

# H. calling solve and sending in non-integer values by piping in file 
```
cat testfile5 | ./sudoku solve

testfile5:
	a b c e d a c e a 
	1 2 4 5 6 4 2 3 4 
	3 2 4 5 6 4 3 2 4 
	3 2 3 5 6 4 3 5 6 
	3 2 4 5 6 4 3 3 5 
	3 4 4 4 6 7 4 2 4 
	3 4 5 6 4 3 4 5 3 
	9 4 5 6 4 3 2 4 5 
	4 5 6 4 2 3 4 5 4

prints:
	Error: Invalid value.
	Error: table is not solvable. 
exit code = 3 (not printed) 
```

# I. calling solve and giving a completely empty table by piping in file
```
cat testfile6 | ./sudoku solve

testfile6: 
	0 0 0 0 0 0 0 0 0
	0 0 0 0 0 0 0 0 0
	0 0 0 0 0 0 0 0 0
	0 0 0 0 0 0 0 0 0
	0 0 0 0 0 0 0 0 0
	0 0 0 0 0 0 0 0 0
	0 0 0 0 0 0 0 0 0
	0 0 0 0 0 0 0 0 0
	0 0 0 0 0 0 0 0 0
prints:
	solved: 
	1 2 3 4 5 6 7 8 9 
	4 5 6 7 8 9 1 2 3 
	7 8 9 1 2 3 4 5 6 
	2 1 4 3 6 5 8 9 7 
	3 6 5 8 9 7 2 1 4 
	8 9 7 2 1 4 3 6 5 
	5 3 1 6 4 2 9 7 8 
	6 4 2 9 7 8 5 3 1 
	9 7 8 5 3 1 6 4 2 
exit code = 0 (not printed)
```

# J. calling with invalid command
```
./sudoku run 

prints:
	Error: 
	Usage:
	sudoku create
	or
	sudoku solve
	or
	sudoku better
exit code = 5 (not printed)
```
# K. calling better in command line and piping in the contents of a file holding sudoku with invalid size
```
cat testfile1 | ./sudoku better

testfile1:
        1 2 3 4 5 5 6 7 8 9 9
        2 4 5 6 7 8 8 9 2 3 9
        1 2 3 5 6 7 8 9 6 5 3
        2 3 4 5 6 7 4 3 2 4 5
        9 8 8 7 7 6 8 9 6 6 6
        3   2 4   4 2   3   3
        3     1     1   1   1
        3 2 1 4     4   2   1
        2 1 4 6 7 8 5 4 3 5 6

prints:

        solved:
        1 2 3 4 5 5 6 7 8
        9 9 2 4 5 6 7 8 8
        9 2 3 9 1 2 3 5 6
        7 8 9 6 5 3 2 3 4
        5 6 7 4 3 2 4 5 9
        8 8 7 7 6 8 9 6 6
        6 3 2 4 4 2 3 3 3
        1 1 1 1 3 2 1 4 4
        2 1 2 1 4 6 7 8 5
exit code = 0 (not printed)
```

# L. calling better and sending in fully completed table by piping in file
```
cat tesfile2 | ./sudoku better

testfile2:
        1 2 3 5 6 3 2 4 5
        1 2 3 5 6 3 2 4 5
        1 2 3 5 6 3 2 4 5
        1 2 3 5 6 3 2 4 5
        1 2 3 5 6 3 2 4 5
        1 2 3 5 6 3 2 4 5
        1 2 3 5 6 3 2 4 5
        1 2 3 5 6 3 2 4 5
        1 2 3 5 6 3 2 4 5

prints:
        solved:
        1 2 3 5 6 3 2 4 5
        1 2 3 5 6 3 2 4 5
        1 2 3 5 6 3 2 4 5
        1 2 3 5 6 3 2 4 5
        1 2 3 5 6 3 2 4 5
        1 2 3 5 6 3 2 4 5
        1 2 3 5 6 3 2 4 5
        1 2 3 5 6 3 2 4 5
        1 2 3 5 6 3 2 4 5
exit code = 0 (not printed)
```

# M. calling better and sending in table which not full and is invalid by piping in file 
```
cat testfile3 | ./sudoku better

testfile3:
        1 1 1 1 1 1 1 1 1
        1 2 0 4 0 5 0 5 5
        1 0 4 0 4 0 4 4 4
        2 6 3 1 3 5 6 4 3
        3 5 6 7 8 9 5 3 2
        3 4 5 6 8 9 6 4 3
        2 4 5 7 8 5 4 0 3
        2 3 0 0 5 0 7 0 3
        3 4 6 7 0 3 5 0 6

prints:
        solved:
        1 1 1 1 1 1 1 1 1
        1 2 0 4 0 5 0 5 5
        1 0 4 0 0 4 0 4 4
        2 6 3 1 3 5 6 4 3
        3 5 6 7 8 9 5 3 2
        3 4 5 6 8 9 6 4 3
        2 4 5 7 8 5 4 0 3
        2 3 0 0 5 0 7 0 3
        3 4 6 7 0 3 5 0 6
exit code = 0 (not printed)
```

# N. calling better and sending in a table with very few values by piping in file
```
cat testfile4 | ./sudoku solve

testfile4:
        1 0 0 0 0 0 0 0 2
        0 0 0 0 0 0 0 0 0
        0 0 0 0 0 0 0 0 0
        0 0 0 0 0 0 0 0 0
        0 0 0 0 0 0 0 0 0
        0 0 0 0 0 0 0 0 0
        0 0 0 0 0 0 0 0 0
        0 0 0 0 0 0 0 0 0
        2 0 0 0 0 0 0 0 3

prints:
        solved:
        1 3 4 5 6 7 8 9 2
        5 2 6 1 8 9 3 4 7
        7 8 9 2 3 4 1 5 6
        3 1 2 4 5 6 7 8 9
        4 5 7 3 9 8 2 6 1
        6 9 8 7 1 2 4 3 5
        8 7 3 9 2 5 6 1 4
        9 4 1 6 7 3 5 2 8
        2 6 5 8 4 1 9 7 3
exit code = 0 (not printed)
```

# O. calling better and sending in non-integer values by piping in file 
```
cat testfile5 | ./sudoku better

testfile5:
        a b c e d a c e a
        1 2 4 5 6 4 2 3 4
        3 2 4 5 6 4 3 2 4
        3 2 3 5 6 4 3 5 6
        3 2 4 5 6 4 3 3 5
        3 4 4 4 6 7 4 2 4
        3 4 5 6 4 3 4 5 3
        9 4 5 6 4 3 2 4 5
        4 5 6 4 2 3 4 5 4

prints:
        Error: Invalid value.
        Error: load_board gave NULL table.
exit code = 4 (not printed)
```

# P. calling better and giving a completely empty table by piping in file
```
cat testfile6 | ./sudoku solve

testfile6:
        0 0 0 0 0 0 0 0 0
        0 0 0 0 0 0 0 0 0
        0 0 0 0 0 0 0 0 0
        0 0 0 0 0 0 0 0 0
        0 0 0 0 0 0 0 0 0
        0 0 0 0 0 0 0 0 0
        0 0 0 0 0 0 0 0 0
        0 0 0 0 0 0 0 0 0
        0 0 0 0 0 0 0 0 0
prints:
        solved:
        1 2 3 4 5 6 7 8 9
        4 5 6 7 8 9 1 2 3
        7 8 9 1 2 3 4 5 6
        2 1 4 3 6 5 8 9 7
        3 6 5 8 9 7 2 1 4
        8 9 7 2 1 4 3 6 5
        5 3 1 6 4 2 9 7 8
        6 4 2 9 7 8 5 3 1
        9 7 8 5 3 1 6 4 2
exit code = 0 (not printed)
```


