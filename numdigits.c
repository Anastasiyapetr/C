#include <stdio.h>

int main () {
	int n,digits=0,i;
	printf ("Enter the number: ");
	scanf ("%d", &n);
	i=n;
	do {
		n/=10;
		digits++;
	} while (n>0);
	printf ("The number %d consists of %d figures\n", i,digits);
	return 0;
}
