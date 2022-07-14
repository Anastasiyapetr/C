#include <stdio.h>
#include <ctype.h>

int main () {
	char first_name,x,soak_up;
	char last_name[20];
	int i;

	printf ("Enter your full name: ");
		
	while ((first_name=getchar())==' ') 
		soak_up=first_name;
	
	x=toupper (first_name);
	
	while (first_name!= ' ') 
		first_name=getchar ();
	
	printf ("You enter the name: ");
	for (i=0;i<20&&(last_name[i]=getchar())!='\n';i++){
		if (last_name[i]==' ') {
			soak_up=last_name[i];
		}
		else
			printf ("%c", last_name[i]);
	}
	
	printf (", %c.\n",x);

	return 0;
	}	

