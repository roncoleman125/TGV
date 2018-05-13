#include <assert.h>
#include "Hand.h"
#include "Player.h"

__host__ __device__ Hand Hand_() {
	Hand hand = { {
			Card_(NO_RANK, NO_SUIT),
			Card_(NO_RANK, NO_SUIT),
			Card_(NO_RANK, NO_SUIT),
			Card_(NO_RANK, NO_SUIT),
			Card_(NO_RANK, NO_SUIT) },
			0, 0, 1.0, NULL };

	return hand;
}

__host__ __device__ Hand Hand_(void* player) {
	Hand hand = { {
			Card_(NO_RANK, NO_SUIT),
			Card_(NO_RANK, NO_SUIT),
			Card_(NO_RANK, NO_SUIT),
			Card_(NO_RANK, NO_SUIT),
			Card_(NO_RANK, NO_SUIT) },
			0, 0, 1.0, player };

	return hand;
}

__host__ __device__ Hand Hand_(Card* card1, Card* card2) {
	Hand hand = { {
			*card1, *card2
		}, 0, 0 };

	return hand;
}


__host__ __device__ Card hit(Player* player) {
	assert(player->size > 0);

	Int sz = player->size;

	return hit(player, sz - 1);
}


__host__ __device__ Card hit(Player* player, Int handno) {
	assert(player->size > 0 && handno < MAX_YOUR_HANDS);

	return hit(&player->hands[handno]);
}

__host__ __device__ Int score(Hand* hand) {
	Int sum = 0;

	Int nAces = 0;

	for (Int k = 0; k < hand->size; k++) {
		Card card = hand->cards[k];
		sum += isFace(&hand->cards[k]) ? 10 : hand->cards[k].rank;

		// If rank == ACE_AS_11 won't be counted here (correctly!)
		if (card.rank == ACE)
			nAces++;
	}

	// Account for soft aces
	for (Int k = 0; k < nAces; k++) {
		if (sum + ACE_AS_11 > 21)
			break;

		sum += ACE_AS_11;
	}

	return sum;
}

__host__ __device__ bool isBusted(Hand* hand) {
	return hand->value > 21;
}

__host__ __device__ bool isCharlie(Hand* hand) {
	return hand->size == 5 && hand->value <= 21;
}

__host__ __device__ bool isBlackjack(Hand* hand) {
	return hand->size == 2 && hand->value == 21;
}

__host__ __device__ bool isBlackjack(void* player, Hand* hand) {
	Player* playor = (Player*)player;

	return isBlackjack(hand) && playor->size == 1;
}

__host__ __device__ Card hit(Hand* hand) {
	Card card = deal();

	hit(hand, &card);

	return card;
}

__host__ __device__ void hit(Hand* hand, Card* card) {
	assert(hand->size < MAX_HAND_CARDS);
	assert(!isBusted(hand));

	Int index = hand->size++;

	hand->cards[index] = *card;

	hand->value = score(hand);

	return;
}

__host__ __device__ bool isPair(Hand* hand) {
	if (hand->size != 2)
		return false;

	Card card1 = hand->cards[0];
	Card card2 = hand->cards[1];

	return card1.rank == card2.rank;
}

__host__ __device__ bool isAcePlusX(Hand* hand) {
	if (hand->size != 2)
		return false;

	Card card1 = hand->cards[0];
	Card card2 = hand->cards[1];

	return (card1.rank == ACE && card2.rank != ACE) || (card1.rank != ACE && card2.rank == ACE);
}

