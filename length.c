#include <stdio.h>

int main () {
	char ch;
	int n;
	printf ("Enter your message: ");

	while ((ch=getchar())!='\n') { 
		n++;
	}
	printf ("Your message was %d character(s) long.\n", n);
	return 0;
}
