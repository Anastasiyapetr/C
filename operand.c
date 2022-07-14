#include <stdio.h>

int main () {
	float a,b,c;
	float v1,v2;
	char op1,op2;
	printf ("Enter an expression with three variables: ");
	scanf ("%f%c%f%c%f",&a,&op1,&b,&op2,&c);

	if (op1=='+')
		v1=a+b;
	else if (op1=='-')
		v1=a-b;
	else if (op1=='/')
		v1=a/b;
	else if (op1=='*')
		v1=a*b;
	else
		printf ("Invalid value\n");

	if (op2=='+')
                v2=v1+c;
        else if (op2=='-')
                v2=v1-c;
        else if (op2=='/')
                v2=v1/c;
        else if (op2=='*')
                v2=v1*c;
        else
                printf ("Invalid value\n");
printf ("The meaning of expression is: %.2f\n",v2);
return 0;
}

