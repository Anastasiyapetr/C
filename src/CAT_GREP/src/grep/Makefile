all: clean n_grep test
n_grep: n_grep.o
	gcc -std=c11 n_grep.o -o n_grep
n_grep.o: n_grep.c
	gcc -c  -std=c11 -Wall -Werror -Wextra n_grep.c -o n_grep.o
clean:
	rm -rf *.o *.log n_grep
rebuild:
	make clean
	make all
test:
	bash test_func_grep.sh
