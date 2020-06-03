#variables
CC = gcc

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(UNITTEST) 
MAKE = make
PROG = sudoku
OBJS = sudomain.o
TEST = testing.sh
LIBS = common/common.a

# testing
FUZZ = fuzzsudoku
UNITTEST = -D MYTEST
FUZZOBJS = fuzzsudoku.o

.PHONY: clean sourcelist test

all: $(FUZZ) $(PROG) 
	make -C common

#rules
$(PROG): $(OBJS) $(LIBS)
	$(CC) $(CFLAGS) $^ -o $@

$(FUZZ): $(FUZZOBJS)  $(LIBS)
	$(CC) $(CFLAGS) $^ -o $@


.PHONY: clean sourcelist test


solve: 
	./$(PROG) solve

create:
	./$(PROG) create

better: 
	./$(PROG) better

fuzz:
	./$(FUZZ) 5   

test:
	bash -v testing.sh 

# dependencies
sudomain.o: $(LIBS)
fuzzsudoku.o: $(LIBS)


# clean up after our compilation
clean:
	rm -rf *.o
	rm -rf $(PROG)
	rm -rf $(FUZZ)
	rm -rf *.dSYM
	rm -rf *core*
	rm -f test/*
