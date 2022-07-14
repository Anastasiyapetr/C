#include <stdio.h>

int main () {
	int d,i1,i2,i3,i4,i5,j1,j2,j3,j4,j5,m,first_sum,second_sum,total,result;
	printf ("Enter UPC:");
	scanf ("%d %1d%1d%1d%1d%1d %1d%1d%1d%1d%1d %d",&d,&i1,&i2,&i3,&i4,&i5,&j1,&j2,&j3,&j4,&j5,&m);

	first_sum=d+i2+i4+j1+j3+j5;
	second_sum=i1+i3+i5+j2+j4;
	total=3*first_sum+second_sum;
	result=9-((total-1)%10);
	if (result==m)
		printf ("VALID");
	else 
		printf ("NOT VALID");
	return 0;
}

