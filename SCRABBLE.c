#include <stdio.h>
#include <ctype.h>

int main () {

	int sum=0;
	int letter[26]={1,3,3,2,1,4,2,3,1,8,5,1,3,1,1,3,10,1,1,1,1,4,4,8,4,10};
	char ch;
	int i,b;

	printf ("Enter a word: ");
	while ((ch=getchar())!='\n') {
		ch=toupper (ch);
		i=(ch-'A');
		b=letter[i];
		sum+=b;
	}
	printf ("The meaning scrabble is: %d\n",sum);
	return 0;
}

	
