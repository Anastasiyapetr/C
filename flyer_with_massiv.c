#include <stdio.h>

int main () {
        int departure[8]={480,583,679,767,840,945,1140,1305};
	int arriving [8]={616,712,811,900,968,1075,1280,1438};
	int i,hour,minute,new_time;
        printf ("Enter a time in 24-hour format: ");
        scanf ("%d:%d",&hour,&minute);

        new_time=hour*60+minute;
	if (new_time>1305) 
		printf ("Closest Departure time will be tommorow at 8:00 AM, arriving at 11:15 AM\n");
	for (i=0;i<7;i++) {
		if (((departure [i]+departure[i+1])/2)>=new_time){

			printf ("Closest Departure time is %d:%.2d",departure[i]/60,departure[i]%60);
			if (departure [i]<=720) {
				printf ("AM,arriving at %d:%.2d",arriving[i]/60,arriving[i]%60);
				if (arriving[i]<=720) 
					printf ("AM\n");
				else 
					printf ("PM\n");
			}
			else 
			printf ("PM,arriving at %d:%.2d PM\n",arriving[i]/60,arriving[i]%60);
		break;
	}
	}
        return 0;
}

