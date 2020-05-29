#variables

CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb
MAKE = make
PROG = sudoku

OBJS = sudoku.o


#rules
$(PROG): $(OBJS) 
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean sourcelist test

solve: 
	./$(PROG) solve

create:
	./$(PROG) create

# clean up after our compilation
clean:
	rm -rf *.o
	rm -rf $(PROG)
	rm -rf *.dSYM