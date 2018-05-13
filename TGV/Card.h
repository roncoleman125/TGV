#pragma once
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "Utils.h"

typedef enum { NO_SUIT = 0, HEARTS = 'H', SPADES = 'S', DIAMONDS = 'D', CLUBS = 'C' } Suit;
typedef enum { NO_RANK = 0, ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING } Rank;

#define ACE_AS_11 10

//#define isAce(rank) (rank == ACE)
//#define isFace(card) (card.rank == JACK || card.rank == QUEEN || card.rank == KING)
//#define is10(card) (card.rank == 10)

typedef struct {
	Rank rank;
	Suit suit;
} Card;

__host__ __device__ Card Card_(Rank rank, Suit suit);
__host__ __device__ Card Card_(Int rank, Suit suit);
__host__ __device__ bool isFace(Card* card);
__host__ __device__ bool isAce(Card* card);
__host__ __device__ bool is10(Card* card);
__host__ __device__ Card deal();
__host__ __device__ Suit randomSuit();
__host__ __device__ Rank randomRank();
//#define randomRank() (random(1, 13))