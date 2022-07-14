#include <stdio.h>


int main () {
        double n, sum=0.0;

        printf ("Enter the numbers (0 for finish): \n");
        scanf ("%lf",&n);
        while (n!=0) {
                sum+=n;
		scanf ("%lf",&n);
        }
        printf ("The sum is:%lf\n", sum);
        return 0;
} 
