# CS50 Project: Sudoku

## Valgrinders, May 2020

# Overview
	The following functions are used by sudoku.c
	1. main: This function checks that the command line argument is valid.
		 The user can call either solve or create. This function then 		       calls either the create or solve function based on the 
		 user input. Both of these functions returns a sudoku board, 
		 which the main function then sends into the print_board 
		 function to print it to the user. 
	2. sudoku_new: This function creates a new sudoku data struct which 
		       is defined within sudoku.c. Memory is allocated for 
		       this new structure, and the 2D array which is 
		       associated with this structure is initialized with 0's.
	3. fill_square: This function fills a set of 3x3 squares within the 
			given sudoku data struct. It fills the table 
			randomly using the shuffle function, but makes sure 
			that all values are valid using the can_fit function.
	4. fill_board: This function fills in valid values in a given sudoku
		       data struct in all spots which are empty. Empty spots
		       are filled with 0's.
	5. remove_num: This function takes a fully filled, valid, sudoku 
		       data struct, and removes a specific number of values
		       from the board. This number is specified by the user. 
		       The function checks to make sure that there is still
		       only one valid solution for the table after the 
		       removal of each value. 
	6. print_board: This functions takes a sudoku data struct and prints
			it to the user in a 9x9 format. 
	7. load_board: This function takes a file pointer, which will be 
		       stdout when it is called within solve function, and 
		       loads the values in that file into a sudoku data 
		       struct. 
	8. is_full: This function checks to see if the given sudoku table is
		    full. It returns true if it is, and false otherwise.
	9. can_fit: This function calls can_fit_column, can_fit_row, and 
		    can_fit_square, in order to determine if the given value
		    is valid based on the position of the square in the 
		    sudoku table.
	10. can_fit_column: This function checks if the given value is valid
			    in the given x, y position in the given sudoku 
			    table with regards to the column in which the 
			    square is found.
	11. can_fit_row: This function checks if the given value is valid
		         in the given x, y position in the given sudoku 
			 table with regards to the row in which the square 
			 is found.
	12. can_fit_square: This function checks if the given value is valid
			    in the given x, y position in the given sudoku 
			    table with regards to the 3x3 square in which 
			    the square is found. 
	13. shuffle: This functions shuffles the elements in a given array of
		     size n, which is also given. This function is used to 
		     shuffle the potential options which can be used as the 
		     value for a square in the sudoku table. 
	14. get_value: This function takes the x and y coordinates for a 
			square in the given sudoku table and returns the 
			value associated with this square.
	15. set_value: This function takes the x and y coordinates for a 
		       square in the given sudoku table and sets the value
		       to be the value given by the user. 
	16. copy_sudoku: This function takes two sudoku data structs and 
			 copies the values from one table into the other 
			 table, creating two identical, but separate, sudoku
			 data structs.
	17. delete_sudoku: This function frees the memory associated with 
			   the given sudoku data struct. 
	18. testfunc: This function performs macros testing on the program.
	
	Some helper modules were used:
		1. create: creates a new sudoku data struct, then fills 
			   this table in 3x3 squares diagonally, from the 
			   top left corner to the bottom right corner. The 
			   module then calls the fill_board function to fill
			   in the remainder of the valus in the board. It then
			   removes 40 spaces from this table, then prints 
			   the edited sudoku table. It creates a copy of this 
			   table which is used to make sure there is only one
			   unique solution for the table. 
		2. solve: module which recursively loops over the given 
		          sudoku data struct, and inserting valid values into
			  the empty spaces, marked with 0's. It returns false
			  if the given table was not solvable.
 
# Pseudocode 
1. execute from a command line as shown in User Interface
2. parse the command line, validate parameters
3. if the user calls create, call create function in create module 
	1. in create module, fill the table with valid values 
	2. remove 40 values from this table while maintaining that there is 
	   one unique, solution for the table 
	3. print the board to the user 
	4. copy the board and use copy to make sure that there is still one 
	   unique solution that is possible for the table
4. if the user calls solve, call solve function in solve module
	1. in solve module, loop over the columns and rows in the given
	   sodoku table, searching for squares whose value is zero, denoting
	   an empty space in table that needs to be filled 
		1. if empty space is found, loop through the possible values
		   that can be used in the table 
		2. for each possible value, check if it is valid with regards
		   to the position of the specific square in the table 
			1. if valid value, set this as the value at this 
			   particular position 
			2. continue recursively calling itself as long as
			   there are empty spaces to be filled 
		3. if none of the values is valid for a particular square, 
		   the table is not solvable, return false 

# Error
	0 - no error
	1 - incorrect number of command line arguments
	2 - given sudoku table was not solvable 
	3 - user entered an argument that was not create or solve 

See TESTING.md for example test runs and their output 
