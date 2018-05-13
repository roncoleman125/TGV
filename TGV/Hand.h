#pragma once
#include "Utils.h"
#include "Card.h"

#define MAX_HAND_CARDS 10

typedef struct {
	Card cards[MAX_HAND_CARDS];
	Int value;
	Int size;
	float bet;
	void* player;
} Hand;

__host__ __device__ Hand Hand_();
__host__ __device__ Hand Hand_(void* player);
__host__ __device__ Hand Hand_(Card* card1, Card* card2);
__host__ __device__ Int score(Hand* hand);
__host__ __device__ Card hit(Hand* hand);
__host__ __device__ void hit(Hand* hand, Card* card);
__host__ __device__ bool isBusted(Hand* hand);
__host__ __device__ bool isCharlie(Hand* hand);

__host__ __device__ bool isBlackjack(Hand* dealer);

/*! \brief Returns true if player has a "natural" blackjack.
*/
__host__ __device__ bool isBlackjack(void* player, Hand* hand);

__host__ __device__ bool isPair(Hand* hand);
__host__ __device__ bool isAcePlusX(Hand* hand);