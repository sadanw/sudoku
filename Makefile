#variables
CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb #$(UNITTEST)
MAKE = make
PROG = sudoku
OBJS = sudoku.o

# testing
FUZZ = fuzzsudoku
FUZZOBJS = fuzzsudoku.o
UNITTEST = -D MYTEST

#rules
$(PROG): $(OBJS) 
	$(CC) $(CFLAGS) $^ -o $@

$(FUZZ): $(FUZZOBJS) 
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean sourcelist test

all: $(PROG) $(FUZZ)

solve: 
	./$(PROG) solve

create:
	./$(PROG) create

better: 
	./$(PROG) better

# dependencies
sudoku.o: sudoku.h solve.h create.h
fuzzsudoku.o: sudoku.h solve.h create.h

# clean up after our compilation
clean:
	rm -rf *.o
	rm -rf $(PROG)
	rm -rf $(FUZZ)
	rm -rf *.dSYM
	rm -rf *core*
