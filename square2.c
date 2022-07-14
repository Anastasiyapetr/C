/*This program prints table of squares with using statements FOR*/

#include <stdio.h>

int main () {
        int i,n;
	char ch;
        printf ("This program prints a table of squares..\n");
        printf ("Enter the number of entries in the table: ");
        scanf ("%d", &n);
	ch = getchar ();
     
        for (i=1;i<=n;i++) {
                printf ("%10d%10d\n", i,i*i);
	if (i%24==0) {
		printf ("Press Enter to continue...");
		ch=getchar();
	}
        }
        return 0;
}


