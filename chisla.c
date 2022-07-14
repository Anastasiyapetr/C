#include <stdio.h>

int main () {
	float a,max;
	printf ("Enter a number: ");
	scanf ("%f", &a);
	max=a;
	if (a<=0)
		break;
	else {
	       while (a)
			max=a;
		printf ("Enter a number: ");
        	scanf ("%f", &a); 
	}
	}

	printf ("The largest number was %.2f\n",max);
	return 0;	

