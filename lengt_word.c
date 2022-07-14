#include <stdio.h>

int main () {
	float gap=1.0;
	float n=0.0;
	char word;
	printf ("Enter the sentences: ");
	while ((word=getchar())!='\n'){
		if (word == ' ')
			gap+=1;
		else 
			n+=1;
	}

	printf ("%.1f\n",n/gap);
       return 0;
}	       
