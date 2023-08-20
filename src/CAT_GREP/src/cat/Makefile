all: n_cat
n_cat: n_cat.o
	gcc -std=c11 n_cat.o -o n_cat
n_cat.o: n_cat.c
	gcc -c -std=c11 -Wall -Werror -Wextra n_cat.c -o n_cat.o
clean:
	rm -rf *.o *.log n_cat
rebuild:
	make clean
	make all

test: 
	bash test_func_cat.sh
