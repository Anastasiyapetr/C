#include <stdio.h>

int main () {
	int x,rem,reverse=0;
	printf ("Enter a number: ");
	scanf ("%d", &x);
	
	do {
		rem=x%10;
		reverse=reverse*10+rem;
		x=x/10;
	}
		while (x>0);

	printf ("%d", reverse);
	return 0;
}
