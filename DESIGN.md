# Sudoku Design Spec
## CS50 Spring 2020
## Lucas Boebel, Haily Fox, Scott Gibbons, Sada Nichols-Worley

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

## User Interface
UI for command line takes one argument, either create or solve.

`./sudoku create`

`./sudoku solve`

## Inputs and outputs
`./sudoku create`

Input: None

Output: a sudoku board with 40 missing values and a unique solution

`./sudoku solve`

Input: An unsolved sudoku board

Output: the solution to the given puzzle

## Functional Decomposition into methods
*main*

*solve*

*create*

*read_puzzle*

*is_valid_puzzle*

*remove_values*

*is_valid_column*

*is_valid_row*

*is_valid_square*

## Pseudocode
**main**

	Validate inputs
	Call `solve` or `create`

**solve**

	Call `read_puzzle`
	While puzzle is not valid:
		Find a zero
		Try a value out of possible values
		If valid column, row, and square:
			Place the value and keep moving
		Else: 
			Add value to list of values that are invalid
			Try another value
		If list of possible values is empty:
			Backtrace

**create**

	Initialize puzzle with all zeros
	Use backtrace algorithm to add values until puzzle is complete
	Use backtrace algorithm to remove 40 values, ensuring there is only one solution


## Dataflow through modules
**solve** and **create** will use backtrace algorithm, which validates a puzzle using `is_valid_column`, `is_valid_row`, and `is_valid_square`

## Major Data structures
Hashtable for backtrace
2D array for sudoku

## Testing plan

1. Test program with incorrect command line arguments.
2. Test the solver with invalid sudoku boards.
3. Perform fuzztesting with a program that generates random boards and pipes them into our solver. 
4. Perform unit testing on individual modules within our program. 
5. Test valid sudoku boards.
6. Use valgrind to test for memory leaks

Detailed information on testing is in [TESTING](TESTING.md).
