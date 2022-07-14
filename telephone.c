#include <stdio.h>
#include <ctype.h>

int main () {
	char ch[15];
	int i;
	printf ("Enter the number of phone (max 15 characters): ");
	
	for (i=0;i<15&&(ch[i]=getchar())!='\n';i++)
	{	
	
	if (ch[i]>='a'&&ch[i]<='z'){
		ch[i]=toupper(ch[i]);}
	if (ch[i]>='A'&&ch[i]<='C') 
		ch[i]='2';
	else if (ch[i]>='D'&&ch[i]<='F')
		ch[i]='3';
	else if (ch[i]>='G'&&ch[i]<='I')
		ch[i]='4';
	else if (ch[i]>='J'&&ch[i]<='L')
		ch[i]='5';
	else if (ch[i]>='M'&&ch[i]<='O')
		ch[i]='6';
	else if (ch[i]>='P'&&ch[i]<='S')
		ch[i]='7';
	else if (ch[i]>='T'&&ch[i]<='V')
		ch[i]='8';
	else if (ch[i]>='W'&&ch[i]<='Y')
		ch[i]='9';
	else 
		ch[i]=ch[i];
	}
	printf ("In form numbers: ");
	for (i=0;i<15;i++) {
	printf ("%c", ch[i]);
}
printf ("\n");
return 0;
}

	
