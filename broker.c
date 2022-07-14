#include <stdio.h>

int main () {
	float comission,value;

	while (1) {
		printf ("Enter the number of business: ");
		scanf ("%f", &value);
		if (value==0) {
			return 0;}
		else if (value<2500.00f)
			comission=30.00f+0.017f*value;
		else if (value<6250.00f)
			comission=56.00f+0.0066f*value;
		else if (value<20000.00f)
                	comission=76.00f+0.0034f*value;
		else if (value<50000.00f)
                	comission=100.00f+0.0022f*value;
		else if (value<500000.00f)
                	comission=155.00f+0.0011f*value;
		else 
			comission=255.00f+0.0009f*value;
		if (comission<39.00f)
			comission=39.00f;

		printf ("Comission is:$%.2f\n", comission);
	}
return 0;
}
