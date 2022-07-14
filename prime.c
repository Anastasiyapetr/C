#include <stdio.h>
#include <stdbool.h>

bool is_prime(int n) {
	int divisor;
	if (n<=1) 
		return false;
	for (divisor=2;divisor*divisor<=n;divisor++)
		if (n%divisor==0)
			return false;
	return true;

}

int main () {
	int n;
	printf ("Enter the number: ");
	scanf ("%d", &n);
	if (is_prime(n))
		printf ("\nPrime number\n");
	else
		printf ("\nComposite number\n");

	return 0;
}




