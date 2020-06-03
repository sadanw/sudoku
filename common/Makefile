OBJS = sudoku.o create.o solve.o
LIB = common.a

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(FLAGS)
CC = gcc
MAKE = make

.PHONY: clean sourcelist

# Rules
$(LIB):
	$(OBJS)
	ar cr $(LIB) $(OBJS)


# Dependencies
solve.o: solve.h sudoku.h
create.o: create.h sudoku.h
sudoku.o: sudoku.h

$(LIB): $(OBJS)
	ar cr $(LIB) $(OBJS)

# clean up after our compilation
clean:
	rm -f core
	rm -f $(LIB) *~ *.o