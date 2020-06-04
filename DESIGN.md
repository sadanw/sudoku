# Sudoku Design Spec
## CS50 Spring 2020
## Lucas Boebel, Hailey Fox, Scott Gibbons, Sada Nichols-Worley

---
layout: page
title: TSE Querier Design Spec
---

Recall the Sudoku Requirements Spec; the **sudoku** is a well known logic puzzle where numbers between 1 and 9 are placed on a 9x9 grid of cells. The placement of numbers has to follow certain rules. There are many variations of Sudoku, but this program only uses the most common version of Sudoku.

A Design spec should contain several sections:

* User interface
* Inputs and Outputs
* Functional decomposition into modules
* Pseudo code for logic/algorithmic flow
* Dataflow through modules
* Major data structures
* Testing plan

Let's look through each.

### User Interface

UI for command line takes one argument, either create, solve, or use better solution.

```
./sudoku create
```

```
./sudoku solve
```

```
./sudoku better
```

### Inputs and outputs

Input: the inputs are both the command-line parameters as shown in the User Interface above, 
and the Sudoku data structures the user enters into stdin. 

Output: When create is called, a Sudoku table is printed with forty of the square representing
empty squares, which is shown using 0's. It is guaranteed that there is a unique solution for
this table. When solve is called, the program fills in any missing spaces in the user-given
table, if it is solvable, and then outputs the completed table to stdout. 


### Functional Decomposition into methods

We anticipate the following modules or functions:
	
	1. *main*, which parses arguments and calls the create and solve modules
	2. *sudoku_new*, which creates a new Sudoku data struct
	3. *fill_square*, which fills a 3x3 square of values in the table at a time
	4. *fill_board*, which fills the remainder of the board with valid values
	5. *remove_num*, which removes values from the board once the full board has been made
	6. *print_board*, which prints the contents of the board to stdout
	7. *load_board*, which loads the board from stdin or from a given file 
	8. *is_full*, which monitors if the table is full yet, which would mean there were  no more empty spots to fill 
	9. *can_fit*, which determines if a given value is valid based on the square's position in the table
	10. *shuffle*, which shuffles the contents of an array so that values can be randomly added to the board, if valid
	11. *get_value*, which is a getter function that returns the value associated with a particular x, y coordinate pair
	12. *set_value*, which is a setter function that takes in a value and assigns it at the given x, y coordinate pair
	13. *copy_sudoku*, which copies the contents of one sudoku table into another table
	14. *delete_sudoku*, which frees the memory associated with the given sudoku data struct 
	15. *testfunc*, which performs Macros testing for the program

And some helper modules:
	1. *create*, which takes a sudoku data struct and fills it with valid values and then removes 40 values, while 
	   ensuring that there is still one, unique solution for the table 
	2. *solve*, which takes a user-given Sudoku table and finds valid values for the empty spaces 
	   found in the table if there are any   

## Pseudocode

1. execute from a command line as shown in the User Interface 
2. parse the command line, validate parameters, and call the other modules based on arguments
3. if *create* is called
	1. *create* new sudoku table by calling *create* function in *create* module 
		1. in *create* module
		2. *create* new table 
		3. fill in values
		4. remove specified number of values
	2. print board
	3. free memory
3. if *solve* is called
	1. load table from stdin
	2. call *solve* module function 
		1. in *solve* module
		2. find empty spaces
		3. test potential options based on if they are valid in the square's position in table 
	3. print board 
	4. free memory 
4. if *better* is called
	1. load board from stdin 
	2. call *better* function 
		1. in *better* 
		2. use list of size 9 to keep track of values that are valid for a given position
		3. use this to fill in the empty spaces in the table 
	3. print board
	4. free memory

**better** provides an alternative algorithm to solve the Sudoku table which is more efficient than the normal *solve* algorithm

A good implementation will not necessarily encode all the above code in a single, deeply-nested function; part of the Implementation Spec is to break the pseudocode down into a cleanly arranged set of functions.


### Dataflow through modules

1. *main* parses parameters and calls the respective module based on the arguments
2. *create* creates a new table with valid values then removes a specified number so there are empty spaces, ensures one unique solution
3. *solve* takes a sudoku table and recusively finds empty spaces then determines valid values for it if the table is solvable 
4. *better* takes a sudoku table and performs the same operations as the *solve* module, albeit using a more efficient algorithm 

**solve** and **create** will use backtrace algorithm, which validates a puzzle using `is_valid_column`, `is_valid_row`, and `is_valid_square`

### Major Data structures
	1. 2D array for Sudoku table

### Testing plan

*Unit testing*. A small test function in `sudoku.c`, called `testfunc()` which performs Macros testing on the program. 

*Integration teting*. Assemble Sudoku table within *create* module then perform operations such as removing values. Assemble Sudoku table by reading in from stdin or filethen can perform operations on this by calling *solve* module. Assemble Sudoku table by reading in from stdin or file then perform operations using *better* function within `sudoku.c`. 
Print updates on operations performed, e.g. `Solved:` along with error messages. 

0. Test the program wiht various forms of incorrect command-line arguments to ensure that its command-line parsing and validation of those parameters works correctly.
 
0. Test the sudoku.c with too many command line arguments- more than one. 

0. Test the sudoku.c with too few command line arguments. 

0. Test the sudoku.c with invalid arguments- anything other than `create`, `solve`, or `better`. 

1. Test *create* module ensuring that there is one, unique solution.

1. Test *solve* module with a variety of different boards in stdin

1. Test *solve* module with a variety of valid and invalid boards by piping in the contents of different files

1. Test *better* module with a variety of valid and invalid boards in stdin

1. Test *better* module with a variety of valid and invalid boards by piping in the contents of different files

2. Perform fuzztesting with a program that generates random boards and pipes them into our solver. 

3. Perform unit testing on individual modules within our program. 

4. Perform Macros testing on the program

7. Use valgrind to test for memory leaks

Detailed information on testing is in [TESTING](TESTING.md).
