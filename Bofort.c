#include <stdio.h>

int main () {
	int speed;
	printf ("Enter the speed of wind:");
	scanf ("%d",&speed);
	if (speed <1)
		printf ("Type of wind is shtil");
	else if (speed<4)
		printf ("Type of wind is light briz");
	else if (speed <28)
		printf ("Type of wind is briz");
	else if (speed <48)
		printf ("Type of wind is power wind");
	else if (speed <63)
		printf ("Type of wind is shtorm");
	else if (speed >63)
		printf ("Type of wind is uragan");
	else 
		printf ("invalid value");
	return 0;
}
