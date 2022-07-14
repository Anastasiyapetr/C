#include <stdio.h>
#define NUM_RATES ((int)(sizeof(value)/sizeof(value[0])))


int main () {
	
	int i,num_years,year,month;
	double value[5];
	float low_rate;
	
	printf ("Enter the rate:" );
	scanf ("%f",&low_rate);
	printf ("\nEnter the number of years: ");
	scanf ("%d", &num_years);

	printf ("\nYears");

	for (i=0;i<NUM_RATES;i++) {
		printf ("%6.2f%%", low_rate+i);
		value[i]=100.00f;
	}
	printf ("\n");

	for (year=1;year<=num_years;year++) {
		printf ("%3d ",year);
		for (i=0;i<NUM_RATES;i++) {
			for (month=1;month<=12;month++)
			value[i] +=((double)(low_rate+i)/12)/100.0*value[i];
			printf ("%7.2f",value[i]);
	}
	printf ("\n");
	}

return 0;
}

