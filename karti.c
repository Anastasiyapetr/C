#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUM_SUITS 4
#define NUM_RANKS 13

int main () {
	bool in_hand[NUM_SUITS][NUM_RANKS]={false};
	int num_cards,suit,rank;
	const char rank_code[]={'2','3','4','5','6','7','8','9','t','j','q','k','a'};
	const char suit_code[]={'c','d','h','s'};
	srand((unsigned)time(NULL));

	printf ("Enter the number of card in hand: ");
	scanf ("%d", &num_cards);

	printf ("\nIn your hand:");

		rank=rand()%NUM_RANKS;

		if (!in_hand[suit][rank]) {
			in_hand[suit][rank]=true;
			num_cards--;
			printf ("%c%c ",rank_code[rank],suit_code[suit]);
		}
	}
	printf ("\n");
	printf ("\nt-10,j-jack,q-queen,k-king,a-ace\nc-clubs,d-diamonds,h-hearts,s-spades\n");
	return 0;
}

