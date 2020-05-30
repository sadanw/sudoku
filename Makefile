#variables

CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb $(UNITTEST)
MAKE = make
PROG = sudoku

OBJS = sudoku.o

# testing
UNITTEST = -D MYTEST


#rules
$(PROG): $(OBJS) 
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean sourcelist test

solve: 
	./$(PROG) solve

create:
	./$(PROG) create

# dependencies
sudoku.o: solve.h create.h

# clean up after our compilation
clean:
	rm -rf *.o
	rm -rf $(PROG)
	rm -rf *.dSYM
	rm -rf *core*
