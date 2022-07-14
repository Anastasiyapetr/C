#include <stdio.h>

int main () {
	int cmd;
	float balance, credit,debet;

	printf ("***ACME checkbook-balancing program***\n");
	printf ("Commands: 0=clear, 1=credit, 2=debit,\n");
	printf ("3=balance,4=exit\n\n");

	for (;;) {
		printf ("Enter command: ");
		scanf ("%d",&cmd);
		switch (cmd) {
		 case 0:
			balance=0.0f; break;
		 case 1:
			printf ("Enter amount of credit: ");
			scanf ("%f",&credit);
			balance+=credit; break;
		 case 2:
			printf ("Enter amount of debit: ");
                        scanf ("%f",&debet);
                        balance-=debet; break;
		 case 3:
			printf ("Current balace is:$%.2f\n", balance);break;
		 case 4: 
			return 0;
		 default: 
			printf ("Commands: 0=clear, 1=credit, 2=debit,\n");
        		printf ("3=balance,4=exit\n\n"); break;
		}
	}
}



