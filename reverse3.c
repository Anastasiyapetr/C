#include <stdio.h>

int main () {
	char ch [100];
	char x;
	int n=1,i;
	printf ("Enter the sentences: ");
	
	for(i=0;(ch[i]=getchar())!='.'||(ch[i]=getchar())!='?'||(ch[i]=getchar())!='!';i++){
		if (ch[i]==' ')
			n+=1;
		if (ch[i]=='?'||ch[i]=='.'||ch[i]=='!')
			x=ch[i];
	}
	printf ("You enter a %d words\n",n);
	printf ("%c", x);
       return 0;
}       

