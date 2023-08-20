.PHONY: all clean gcov_report decimal.a remove_decimal linter cppcheck leaks

CC = gcc
FLAGS = -Wall -Wextra -Werror -std=c11
TEST_LIB = decimal
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

all: clean Sdecimal.a test

test: decimal.a
	$(CC) $(FLAGS) -o a.out $(TESTFILE).c $(TEST_LIB).a $(LIBS_FOR_CHECK_PCKG) $(GCOV_FLAG)
	./a.out

leak:
	sudo valgrind --log-file="leak.log" ./a.out 

leakr:
	grep -e "ERROR SUMMARY:" leak.log

clean:
	rm -f *.a *.o *.so *.out *.info *.gcno *.gcda leak.log $(TESTFILE)
	rm -rf report
	rm -rf *.gch

gcov_report: decimal.a 
	$(CC) $(FLAGS) $(GCOV_FLAG) $(TEST_LIB).c $(TESTFILE).c $(LIBS_FOR_CHECK_PCKG) -o $(TESTFILE)
	./$(TESTFILE)
	lcov -t "test" -o $(TESTFILE).info -c -d .
	genhtml -o report $(TESTFILE).info

decimal.a: remove_decimal.a
	$(CC) -c $(FLAGS) $(TEST_LIB).c
	ar rc $(TEST_LIB).a *.o
	ranlib $(TEST_LIB).a
	rm -rf *.o

remove_decimal.a:
	rm -f *.a *.o

linter:
	clang-format -n -style=google *.c *.h 

linteri:
	clang-format -i -style=google *.c *.h 

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h
