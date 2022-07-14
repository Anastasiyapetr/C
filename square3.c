/*This program prints table of squares with using statements ODD*/

#include <stdio.h>

int main () {
        int i,n;

        printf ("This program prints a table of squares..\n");
        printf ("Enter the number of entries in the table: ");
        scanf ("%d", &n);

        i=1;

        for (i;i<=n;i++) {
                printf ("%10d%10d\n",i,i*i);
        }
        return 0;
}


