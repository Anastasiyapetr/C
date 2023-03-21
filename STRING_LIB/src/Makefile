.PHONY: all clean n_string.a gcov_report

CC = gcc
FLAGS = -Wall -Wextra -Werror -std=c11
TEST_LIB = n_string
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

all: clean n_string.a test

test: n_string.a
	checkmk clean_mode=1 $(TESTFILE).check > $(TESTFILE).c
	$(CC) $(FLAGS) -o a.out $(TESTFILE).c $(TEST_LIB).a $(LIBS_FOR_CHECK_PCKG) $(GCOV_FLAG)
	./a.out

gcov_report: n_string.a 
	$(CC) $(FLAGS) $(GCOV_FLAG) $(TEST_LIB).c $(TESTFILE).c $(LIBS_FOR_CHECK_PCKG) -o $(TESTFILE)
	./$(TESTFILE)
	lcov -t "..." -o $(TESTFILE).info -c -d .
	genhtml -o report $(TESTFILE).info

remove_s21_string.a:
	rm -f *.a *.o

clean:
	rm -f *.a *.o *.so *.out $(TESTFILE) $(TESTFILE).c *.info *.gcno *.gcda
	rm -rf report
	rm -rf *.gch

n_string.a: remove_s21_string.a
	$(CC) -c $(FLAGS) $(TEST_LIB).c
	ar rc $(TEST_LIB).a *.o
	ranlib $(TEST_LIB).a
