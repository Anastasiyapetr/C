#include <stdio.h>

int main () {
	int dept1,dept2,dept3,dept4,dept5,dept6,dept7,dept8,hour, minute,new_time;
	char ch1,ch2;
	printf ("Enter a time in 12-hour format: ");
	scanf ("%d:%d%c%c",&hour,&minute,&ch1,&ch2);
	
	new_time=hour*60+minute;
	dept1=8*60;
	dept2=9*60+43;
	dept3=11*60+19;
	dept4=12*60+47;
	dept5=14*60;
	dept6=15*60+45;
	dept7=19*60;
	dept8=21*60+45;
	
	if (ch1=='p'||ch1=='P'||ch2=='p'||ch2=='P') {
		new_time=new_time+12*60;
	}

	if (new_time <=(dept1+dept2)/2)
		printf ("Closet Departure time is 8:00 AM, arriving at 10:16 AM\n");
	else if (new_time <=(dept2+dept3)/2)
                printf ("Closet Deparute time is 9:43AM, arriving at 11:52 AM\n");

	else if (new_time <=(dept3+dept4)/2)
                printf ("Closet Departure time is 11:19 AM, arriving at 1:31 PM\n");
	else if (new_time<=(dept4+dept5)/2)
		printf ("Closet Deparute time is 12:47PM, arriving at 3:00 PM\n");
	else if (new_time<=(dept5+dept6)/2)
                printf ("Closet Deparute time is 2:00PM, arriving at 4:08 PM\n");
	else if (new_time<=(dept6+dept7)/2)
                printf ("Closet Deparute time is 3:45PM, arriving at 5:55 PM\n");
	else if (new_time<=(dept7+dept8)/2)
                printf ("Closet Deparute time is 7:00PM, arriving at 9:20 PM\n");

	else 		
		printf ("Closet Deparute time is 9:45PM, arriving at 11:58 PM\n");
	return 0;
}


