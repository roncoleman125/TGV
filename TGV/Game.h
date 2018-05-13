#pragma once
#include "Strategy.h"
#include "Player.h"

#define PAYOFF_BLACKJACK (1.5f)
#define PAYOFF_CHARLIE (2.0f)
#define PAYOFF_PUSH (0.0f)

#define WINS 0
#define BLACKJACKS 1
#define CHARLIES 2
#define LOSSES 3
#define BUSTS 4
#define DEALER_BLACKJACKS 5
#define PUSHES 6

typedef struct {
	int count[7];
	int nohands;
	float pl;
} Game;

/*! \brief Game constructor */
Game Game_();

/*! \brief Starts a game.
\param strategy Strategy to use
\param ngames Number of games to play
\param seed Random seed
\return Statistics for n games
*/
Game start(Strategy* strategy, int ngames, int seed);

/*! \brief Plays a game with a strategy. */
__host__ __device__ void play(Strategy* strategy, Game* statistics);
__host__ __device__ void play(Player* player, Card* upcard);
__host__ __device__ void play(Hand* dealer, Player* player, Game* statistics);
__host__ __device__ void playout(Hand* hand, Card* upcard);
__host__            void output(Game* statistics, int method);
