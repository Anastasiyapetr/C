#include <stdio.h>

int main () {
	int grade;
	printf ("Enter the grade: ");
	scanf ("%d",&grade);

	 if (grade < 0 || grade > 100)
         	printf ("Invalid value\n");
		return 0;
		

	switch (grade/10) {
		case 10:case 9:
			printf ("Letter grade is A\n");
			break;
		case 8:
			printf ("Letter grade is B\n");
			break;
		case 7:
			printf ("Letter grade is C\n");
			break;
		case 6:
			printf ("Letter grade is D\n");
			break;
		case 5:case 4: case 3: case 2: case 1:case 0: 
			printf ("Letter grade is F\n");
			break;
		}
	
		return 0;
}

