#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Player.h"
#include "Strategy.h"
#include "Game.h"

/*
void play(Player* yours, Card* upcard);
void playout(Hand* hand, Card* upcard);
void play(Strategy* strategy, Game* statistics);
void split(Hand* hand, Card* upcard);

void init(Player* player);
*/

/*
int main_(int argc, char** argv) {
printf("hello\n");

return 0;
}
*/

__host__ __device__ static void split(Hand* hand, Card* upcard);
__host__ __device__ static Play getPlay(Hand* hand, Card* upcard);
__host__ __device__ static void splitbackup(Hand* hand, Card* upcard);

__host__ __device__ Game Game_() {
	return{ { 0, 0, 0, 0, 0, 0, 0 }, 0, 0.0 };
}

__host__ __device__ Game start(Strategy* strategy, int ngames, int seed) {
	srand(seed);

	Game statistics = Game_();

	assert(statistics.pl == 0);

	for (int gameno = 0; gameno < ngames; gameno++) {
		play(strategy, &statistics);
	}

	return statistics;
}

__host__ __device__ void play(Strategy* strategy, Game* statistics) {
	static int gameno = 0;
	if (gameno == 256)
		gameno = gameno;

	// Create the heads-up game
	Player player = Player_(strategy);
	init(&player);

	assert(player.pl == 0.0);

	Hand dealer = Hand_();

	// Deal the initial round
	hit(&player);

	hit(&dealer);

	hit(&player);

	hit(&dealer);

	Card upcard = dealer.cards[0];

	// Play the player's hand
	play(&player, &upcard);

	// Player the dealer's hand
	play(&dealer, &player, statistics);

	// Save the statistics.
	statistics->pl += player.pl;

	statistics->nohands += player.size;

	int sum = 0;

	int n = sizeof(statistics->count) / sizeof(int);

	for (int index = 0; index < n; index++)
		sum += statistics->count[index];

	gameno++;
}

/*! \brief Play the player's hand. */
__host__ __device__ void play(Player* player, Card* upcard) {
	assert(player->pl == 0);

	playout(&player->hands[0], upcard);
}

/*! \brief Playout a hand, recursively, if needed. */
__host__ __device__ void playout(Hand* hand, Card* upcard) {
	assert(!isBusted(hand));
	assert(hand->bet != 0);

	Play play = getPlay(hand, upcard);

	switch (play) {
	case NO_PLAY:
		assert(false);
		break;

	case STAY:
		break;

	case HIT:
		hit(hand);

		if (isBusted(hand) || isBlackjack(hand))
			return;
		/*
		if (isCharlie(hand))
		return;
		*/

		playout(hand, upcard);
		break;

	case DOUBLE_DOWN:
		assert(hand->size == 2);

		hand->bet *= 2.0;

		hit(hand, upcard);
		break;

	case SPLIT:
		//assert(isPair(hand));

		split(hand, upcard);
		break;
	}
}

__host__ __device__ void split(Hand* hand1, Card* upcard) {
	assert(hand1->size == 2);

	// If there's a split overflow, fallback to nonn-split
	Player* player = (Player*)hand1->player;

	if (player->size >= MAX_YOUR_HANDS) {
		splitbackup(hand1, upcard);
		return;
	}

	// Allow splitting Aces once and hit each Ace once without playthrough.
	bool playThrough = true;

	if (isPair(hand1) && hand1->cards[0].rank == ACE)
		playThrough = false;

	// Make the new hand
	Hand newHand = Hand_(player);

	// Get card from 1st hand
	Card card = hand1->cards[1];
	hand1->size--;

	// Hit the 1st hand with new card from the deck
	hit(hand1);

	// Hit 2nd hand with card from 1st hand and the deck
	hit(&newHand, &card);
	hit(&newHand);

	// Add 2nd hand to the player
	Int index = add(player, &newHand);
	Hand* hand2 = &player->hands[index];

	assert(hand1->size == 2 && hand2->size == 2);
	assert(player->size > 1);

	// Not playing through after hitting
	if (!playThrough)
		return;

	// Play through each hand recursively
	playout(hand1, upcard);

	playout(hand2, upcard);
}

__host__ __device__ void splitbackup(Hand* hand, Card* upcard) {
	Player* player = (Player*)hand->player;

	Strategy* strategy = player->strategy;

	Play play = NO_PLAY;

	if (hand->value >= 12) {
		play = doSection1(hand, upcard, strategy);
	}
	else {
		play = doSection2(hand, upcard, strategy);
	}

	switch (play) {
	case STAY:
		break;

	case HIT:
		hit(hand);

		if (!isBusted(hand))
			playout(hand, upcard);

		break;

	case DOUBLE_DOWN:
		hit(hand);

		hand->bet *= 2.0;

		break;

	case SPLIT:
		// A split here is tantamount to STAY
		//		assert(false);

		break;

	case NO_PLAY:
		assert(false);
		break;
	}

	return;
}

__host__ __device__ void play(Hand* dealer, Player* player, Game* statistics) {
	int remaining = player->size;

	// Payout the hands we can at this point...
	for (int index = 0; index < player->size; index++) {
		Hand* hand = &player->hands[index];

		assert(hand->bet > 0);
		assert(hand->player == player);

		if (isBusted(hand)) {
			player->pl -= hand->bet;

			statistics->count[BUSTS]++;

			remaining--;
		}
		// A+10 on split hand not "natural" blackjack and doesn't receive bonus.
		// See https://en.wikipedia.org/wiki/Aces_and_eights_(blackjack).
		else if (isBlackjack(player, hand)) {
			player->pl += (hand->bet * PAYOFF_BLACKJACK);

			statistics->count[BLACKJACKS]++;

			remaining--;
		}
		/*
		else if (isCharlie(hand)) {
		player->pl += (hand->bet * PAYOFF_CHARLIE);

		statistics->count[CHARLIES]++;

		remaining--;
		}
		*/
	}

	// If no hands remaining, the dealer does not have to play
	if (remaining == 0)
		return;

	// Dealer stands on 17 or higher (soft or otherwise)
	while (dealer->value < 17) {
		hit(dealer);
	}

	// Test all the remaining hands
	for (int index = 0; index < player->size; index++) {
		Hand* hand = &player->hands[index];

		// Validate hand played through
		assert(hand->size >= 2);

		// Validate double-down
		if (hand->bet == 2)
			assert(hand->size == 3);

		// We've handle these above
		if (isBusted(hand) || isBlackjack(player, hand))
			continue;

		// Dealer blackjack beats all except player blackjack and charlie
		if (isBlackjack(dealer)) {
			player->pl -= hand->bet;
			statistics->count[DEALER_BLACKJACKS]++;
		}

		// If dealer broke, pay the player
		else if (isBusted(dealer)) {
			player->pl += hand->bet;
			statistics->count[WINS]++;
		}

		// If dealer lost, pay the player
		else if (dealer->value < hand->value) {
			player->pl += hand->bet;
			statistics->count[WINS]++;
		}

		// If player lost, collect for house
		else if (dealer->value > hand->value) {
			player->pl -= hand->bet;
			statistics->count[LOSSES]++;
		}

		// If hands same, nobody wins or loses
		else if (dealer->value == hand->value) {
			player->pl += 0;
			statistics->count[PUSHES]++;
		}
		else // No other condidtions apply
			assert(false);
	}
}

__host__ __device__ Play getPlay(Hand* hand, Card* upcard) {
	Strategy* strategy = ((Player*)hand->player)->strategy;

	Play play1 = NO_PLAY;

	if (isPair(hand))
		play1 = doSection4(hand, upcard, strategy);

	else if (isAcePlusX(hand))
		play1 = doSection3(hand, upcard, strategy);

	else if (hand->value >= 5 && hand->value <= 11)
		play1 = doSection2(hand, upcard, strategy);

	else
		play1 = doSection1(hand, upcard, strategy);

	////////
	/*
	Int dealer = isFace(upcard) ? 10 : upcard->rank;

	if (dealer == ACE)
	dealer += ACE_AS_11;

	Play play2 = NO_PLAY;

	if (isPair(hand) && (hand->cards[0].rank == ACE || hand->cards[0].rank == EIGHT))
	play2 = SPLIT;

	else if (hand->value == 11 && hand->size == 2)
	play2 = DOUBLE_DOWN;

	else if (hand->value <= 10)
	play2 = HIT;

	else if (hand->value >= 17)
	play2 = STAY;

	else if (hand->value <= 16 && dealer <= 6)
	play2 = STAY;

	else if (hand->value <= 16 && dealer > 6)
	play2 = HIT;

	else
	assert(false);

	if (play1 != play2)
	play1 = play1;
	*/

	return play1;
}

__host__ void output(Game* statistics, int method) {
	int n = sizeof(statistics->count) / sizeof(int);
	int nohands = 0;
	for (int index = 0; index < n; index++)
		nohands += statistics->count[index];
	double mean = statistics->pl / nohands;

	assert(nohands == statistics->nohands);
	printf("%9.6f %-9d %-9d %-9d %-9d %-9d %-9d %-9d %-9d\n",
		mean, nohands,
		statistics->count[WINS],
		statistics->count[BLACKJACKS],
		statistics->count[CHARLIES],
		statistics->count[LOSSES],
		statistics->count[BUSTS],
		statistics->count[DEALER_BLACKJACKS],
		statistics->count[PUSHES]);
}
