#include <stdio.h>

double average (double a,double b) {
	return (a+b)/2;
}

int main (){
	double x,y,z;
	printf ("Enter three numbers: ");
	scanf ("%lf %lf %lf", &x,&y,&z);

	printf ("\nThe average value %.1lf and %.1lf is:%.2lf ", x,y,average (x,y));
	printf ("\nThe average value %.1lf and %.1lf is:%.2lf ", y,z,average (y,z));
	printf ("\nThe average value %.1lf and %.1lf is:%.2lf ", x,z,average (x,z));
	return 0;
}
