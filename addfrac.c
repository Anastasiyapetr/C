#include <stdio.h>

int main () {
	char ch;
	int a,b,c,d;
	
	int n=0,m=0;

	printf ("Enter two drods with operand: ");
	scanf ("%d/%d%c%d/%d",&a,&b,&ch,&c,&d);
	if (ch=='+') {
		if (b%d==0){
			n=b;
			m=a+c*(b/d);
		}
		else if (d%b==0){
			n=d;
			m=c+a*(d/b);
		}
		else {
			n=b*d;
			m=a*d+c*b;
	}
	}
	else if (ch=='-') {
		if (b%d==0) {
			n=b;
			m=a-c*(b/d);
		}
		else if (d%b==0){
                        n=d;
                        m=c-a*(d/b);
                }
                else {
                        n=b*d;
                        m=a*d-c*b;
		}
	}
	else if (ch=='*') {
		m=a*c;
		n=b*d;
	}
	else if (ch=='/') {
		m=a*d;
		n=b*c;
	}
	else {
		printf ("Invalid value\n");
	}

	printf ("Value is:%d/%d\n",m,n);

return 0;
}
