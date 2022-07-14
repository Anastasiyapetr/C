/*This program prints table of squares with using statements WHILE*/

#include <stdio.h>

int main () {
	int n;
	short int i;
	printf ("This program prints a table of squares..\n");
	printf ("Enter the number of entries in the table: ");
	scanf ("%d", &n);
	i=1;
	while (i<=n) {
		printf ("%10hd%10hd\n", i,i*i);
		i++;
	}
	return 0;
}

