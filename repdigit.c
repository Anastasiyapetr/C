#include <stdio.h>
#include <stdbool.h>

int main () {
	bool digit_seen[10]={false};
	int [10];
	int digit,i;
	long n;

	printf ("Enter a number: ");
	scanf ("%ld", &n);

	while (n>0) {
		digit =n%10;
		if (digit_seen[digit])
		int[digit]=digit;
		else digit_seen[digit]=true;
		n/=10;
	}

	if (int[digit]!=0)
		printf ("the repeating numbers is %d",int[digit]);
	else 
		printf ("there isn't a repeating digit\n");

	return 0;
}


