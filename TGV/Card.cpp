#include <assert.h>
#include "Card.h"

__host__ __device__ Card Card_(Rank rank, Suit suit) {
	Card card = { rank, suit };
	return card;
}

__host__ __device__ Card Card_(Int rank, Suit suit) {
	Card card = { (Rank)rank, suit };
	return card;
}

__host__ __device__ Card deal() {
	// Get a random suit
	Suit suit = randomSuit();

	// Get a rank
	Rank rank = randomRank();

	// Make a card
	Card card = Card_(rank, suit);
	return card;
}

__host__ __device__ bool isFace(Card* card) {
	return card->rank == JACK || card->rank == QUEEN || card->rank == KING;
}

__host__ __device__ bool isAce(Card* card) {
	return card->rank == ACE;
}

__host__ __device__ bool is10(Card* card) {
	return isFace(card) || card->rank == TEN;
}

__host__ __device__ Suit randomSuit() {
	Suit suits[] = { HEARTS, SPADES, DIAMONDS, CLUBS };

	Int index = random(0, 3);

	return suits[index];
}

__host__ __device__ Rank randomRank() {
	Rank rank = (Rank)random(ACE, KING);

	assert(rank >= ACE && rank <= KING);

	//return (Rank) random(ACE, KING);
	return rank;
}