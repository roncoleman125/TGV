#pragma once
#include "Utils.h"
#include "Hand.h"
#include "Strategy.h"

#define MAX_YOUR_HANDS 4

/*! @brief Represents the player with all its hands.
*/
typedef struct {
	Hand hands[MAX_YOUR_HANDS];
	Int size;
	Strategy* strategy;
	float pl;
} Player;

__host__ __device__ Player Player_(Strategy* strategy);

/*! \brief Initializes a player. */
__host__ __device__ void init(Player* player);

__host__ __device__ Int add(Player* player, Hand* hand);
__host__ __device__ Card hit(Player* player);
__host__ __device__ Card hit(Player* player, Int handno);