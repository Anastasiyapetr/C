.PHONY: all test clean RomanNumerals.o

CC = gcc
FLAGS = -Wall -Wextra -Werror -std=c11
TEST_LIB = RomanNumerals
TESTFILE = test
GCOV_FLAG = --coverage

LIBS_FOR_CHECK_PCKG =
D_OS =
OS = $(shell uname -s)
ifeq ($(OS), Linux)
	LIBS_FOR_CHECK_PCKG = -lcheck -lsubunit -lm -lpthread -lrt
	D_OS = -D __My_Linux__
else
	LIBS_FOR_CHECK_PCKG = -lcheck -lm -lpthread
	D_OS = -D __My_APPLE__
endif

all: clean RomanNumerals.o test

test: RomanNumerals.o
	$(CC) $(FLAGS) -o a.out $(TESTFILE).c $(TEST_LIB).o $(LIBS_FOR_CHECK_PCKG) $(GCOV_FLAG)
	./a.out
	rm -f *.o

clean:
	rm -f *.o *.so *.out *.info *.gcno *.gcda
	rm -rf report
	rm -rf *.gch

RomanNumerals.o: RomanNumerals.o
	$(CC) -c $(FLAGS) $(TEST_LIB).c

