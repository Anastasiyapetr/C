#include <stdio.h> 
#define LEN ((int)(sizeof(a)/sizeof(a[0]))) 

int main () {
	int a[10] ,i;
	
	printf ("Enter 10 numbers: ");
	for (i=0;i<LEN;i++) {
		scanf ("%d",&a[i]);
	}

	printf ("\nIn reverse order:");
	
	for (i=LEN-1;i>=0;i--)
		printf ("%d ", a[i]);
	printf ("\n");

	return 0;
}
