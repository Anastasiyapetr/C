#include <stdio.h>

int main () {
	int number;

	printf ("Enter a two-digit number: ");
	scanf ("%d", &number);

	if (number<10 || number >99){
		printf ("Invalid value\n");
		return 0;
	}
	
	printf ("You enter the number: ");
	if (number >10 && number <20)
		switch (number) {
			case 11: printf ("""Eleven""\n"); break;
			case 12: printf ("""Twelve""\n");break;
			case 13: printf ("""Thirteen""\n"); break;
			case 14: printf ("Forteen\n"); break;
			case 15: printf ("Fifteen\n"); break;
                	case 16: printf ("Sixteen\n");break;
                	case 17: printf ("Seventeen\n"); break;
			case 18: printf ("Eighteen\n"); break;
			case 19: printf ("Nighteen\n"); break;
	}
	else {
		switch (number / 10) {
			case 1:printf ("ten"); break;
			case 2:printf ("twenty"); break;
			case 3:printf ("thitry"); break;
			case 4:printf ("forty"); break;
			case 5:printf ("fifty");break;
			case 6:printf ("sixty");break;
			case 7:printf ("seventy"); break;
			case 8:printf ("eighty"); break;
			case 9:printf ("ninety"); break;
	}
		switch (number%10) {
			case 1:printf (" one\n"); break;
			case 2:printf (" two\n"); break;
			case 3:printf (" three\n"); break;
			case 4:printf (" four\n"); break;
			case 5:printf (" five\n"); break;
			case 6:printf (" six\n"); break;
			case 7:printf (" seven\n"); break;
			case 8:printf (" eight\n"); break;
			case 9:printf (" nine\n"); break;
	}
	}
	return 0;
}
