#include <stdio.h>

int main () {
	int h,m;
	char ch1,ch2;

	printf ("Please enter the time in 12-hours format: ");
	scanf ("%d:%d%c%c",&h,&m,&ch1,&ch2);

	if (ch1=='p'||ch1=='P'||ch2=='p'||ch2=='P') {

	h=h+12;
}
	printf ("The equivalent 24-hour time is: %.2d:%.2d\n",h,m);
	return 0;
}

