#include <assert.h>
#include "Strategy.h"

__host__ __device__ Strategy Strategy_() {
	Strategy s = {
		0.0,
		{
			//          2  3  4  5  6  7  8  9  T  A
			/*21*/		X, X, X, X, X, X, X, X, X, X, // Section I: lower=0, upper=9
			/*20*/		X, X, X, X, X, X, X, X, X, X,
			/*19*/		X, X, X, X, X, X, X, X, X, X,
			/*18*/		X, X, X, X, X, X, X, X, X, X,
			/*17*/		X, X, X, X, X, X, X, X, X, X,
			/*16*/		X, X, X, X, X, X, X, X, X, X,
			/*15*/		X, X, X, X, X, X, X, X, X, X,
			/*14*/		X, X, X, X, X, X, X, X, X, X,
			/*13*/		X, X, X, X, X, X, X, X, X, X,
			/*12*/		X, X, X, X, X, X, X, X, X, X,

			/*11*/		X, X, X, X, X, X, X, X, X, X, // Section II: lower=10, upper=16
			/*10*/		X, X, X, X, X, X, X, X, X, X,
			/*9 */		X, X, X, X, X, X, X, X, X, X,
			/*8 */		X, X, X, X, X, X, X, X, X, X,
			/*7 */		X, X, X, X, X, X, X, X, X, X,
			/*6 */		X, X, X, X, X, X, X, X, X, X,
			/*5 */		X, X, X, X, X, X, X, X, X, X,
			/*4 */		X, X, X, X, X, X, X, X, X, X, // Accomodate limited splits

			/*A,K */	X, X, X, X, X, X, X, X, X, X, // Section III: lower=17, upper=25
			/*A,Q */	X, X, X, X, X, X, X, X, X, X,
			/*A,J */	X, X, X, X, X, X, X, X, X, X,
			/*A,T */	X, X, X, X, X, X, X, X, X, X,
			/*A,9 */	X, X, X, X, X, X, X, X, X, X,
			/*A,8 */	X, X, X, X, X, X, X, X, X, X,
			/*A,7 */	X, X, X, X, X, X, X, X, X, X,
			/*A,6 */	X, X, X, X, X, X, X, X, X, X,
			/*A,5 */	X, X, X, X, X, X, X, X, X, X,
			/*A,4 */	X, X, X, X, X, X, X, X, X, X,
			/*A,3 */	X, X, X, X, X, X, X, X, X, X,
			/*A,2 */	X, X, X, X, X, X, X, X, X, X,

			/*A,A */	X, X, X, X, X, X, X, X, X, X, // Section IV: lower=26, upper=35
			/*T,K */	X, X, X, X, X, X, X, X, X, X,
			/*T,Q */	X, X, X, X, X, X, X, X, X, X,
			/*T,J */	X, X, X, X, X, X, X, X, X, X,
			/*T,T */	X, X, X, X, X, X, X, X, X, X,
			/*9,9 */	X, X, X, X, X, X, X, X, X, X,
			/*8,8 */	X, X, X, X, X, X, X, X, X, X,
			/*7,7 */	X, X, X, X, X, X, X, X, X, X,
			/*6,6 */	X, X, X, X, X, X, X, X, X, X,
			/*5,5 */	X, X, X, X, X, X, X, X, X, X,
			/*4,4 */	X, X, X, X, X, X, X, X, X, X,
			/*3,3 */	X, X, X, X, X, X, X, X, X, X,
			/*2,2 */	X, X, X, X, X, X, X, X, X, X,
		},
		{{ 0,  9 },
		{ 10, 17 },
		{ 18, 29 },
		{ 30, 42 } }
	};
	return s;
}

__host__ __device__ Strategy BasicStrategy_() {
	Strategy s = {
		0.0,
		{
			//          2  3  4  5  6  7  8  9  T  A
			/*21*/		S, S, S, S, S, S, S, S, S, S, // Section I: lower=0, upper=9
			/*20*/		S, S, S, S, S, S, S, S, S, S,
			/*19*/		S, S, S, S, S, S, S, S, S, S,
			/*18*/		S, S, S, S, S, S, S, S, S, S,
			/*17*/		S, S, S, S, S, S, S, S, S, S,
			/*16*/		S, S, S, S, S, H, H, H, H, H,
			/*15*/		S, S, S, S, S, H, H, H, H, H,
			/*14*/		S, S, S, S, S, H, H, H, H, H,
			/*13*/		S, S, S, S, S, H, H, H, H, H,
			/*12*/		H, H, S, S, S, H, H, H, H, H,

			/*11*/		D, D, D, D, D, D, D, D, D, H, // Section II: lower=10, upper=17
			/*10*/		D, D, D, D, D, D, D, D, H, H,
			/*9 */		H, D, D, D, D, H, H, H, H, H,
			/*8 */		H, H, H, H, H, H, H, H, H, H,
			/*7 */		H, H, H, H, H, H, H, H, H, H,
			/*6 */		H, H, H, H, H, H, H, H, H, H,
			/*5 */		H, H, H, H, H, H, H, H, H, H,
			/*4 */		H, H, H, H, H, H, H, H, H, H, // Accomodate limited splits

			/*A,K */	S, S, S, S, S, S, S, S, S, S, // Section III: lower=18, upper=29
			/*A,Q */	S, S, S, S, S, S, S, S, S, S,
			/*A,J */	S, S, S, S, S, S, S, S, S, S,
			/*A,T */	S, S, S, S, S, S, S, S, S, S,
			/*A,9 */	S, S, S, S, S, S, S, S, S, S,
			/*A,8 */	S, S, S, S, S, S, S, S, S, S,
			/*A,7 */	S, D, D, D, D, S, S, H, H, H,
			/*A,6 */	H, D, D, D, D, H, H, H, H, H,
			/*A,5 */	H, H, D, D, D, H, H, H, H, H,
			/*A,4 */	H, H, D, D, D, H, H, H, H, H,
			/*A,3 */	H, H, H, D, D, H, H, H, H, H,
			/*A,2 */	H, H, H, D, D, H, H, H, H, H,

			/*A,A */	P, P, P, P, P, P, P, P, P, P, // Section IV: lower=30, upper=42
			/*T,K */	S, S, S, S, S, S, S, S, S, S,
			/*Q,Q */	S, S, S, S, S, S, S, S, S, S,
			/*J,J */	S, S, S, S, S, S, S, S, S, S,
			/*T,T */	S, S, S, S, S, S, S, S, S, S,
			/*9,9 */	P, P, P, P, P, S, P, P, S, S,
			/*8,8 */	P, P, P, P, P, P, P, P, P, P,
			/*7,7 */	P, P, P, P, P, P, H, H, H, H,
			/*6,6 */	P, P, P, P, P, H, H, H, H, H,
			/*5,5 */	D, D, D, D, D, D, D, D, H, H,
			/*4,4 */	H, H, H, P, P, H, H, H, H, H,
			/*3,3 */	P, P, P, P, P, P, H, H, H, H,
			/*2,2 */	P, P, P, P, P, P, H, H, H, H,
		},
		{ { 0,   9 },
		{ 10, 17 },
		{ 18, 29 },
		{ 30, 42 } }
	};
	return s;
}

#define RANK(rank) (rank >= 10 ? 10 : rank)

/*
*/
__host__ __device__ Play doSection4(Hand* hand, Card* upcard, Strategy* strategy) {
	assert(hand->size == 2);

	Card card1 = hand->cards[0];
	Card card2 = hand->cards[1];

	assert(card1.rank == card2.rank);

	Int offset = 0;

	if (!isAce(&card1))
		offset = KING - card1.rank + 1;
	assert(offset >= 0);

	Int row = strategy->jumpTab[SECTION4].lower + offset;
	assert(row >= strategy->jumpTab[SECTION4].lower && row <= strategy->jumpTab[SECTION4].upper);

	Int col = isAce(upcard) ? 9 : RANK(upcard->rank) - 2;

	Int index = row * 10 + col;

	Play play = strategy->rules[index];

	return play;
}

__host__ __device__ Play doSection3(Hand* hand, Card* upcard, Strategy* strategy) {
	assert(hand->size == 2);

	Card card1 = hand->cards[0];
	Card card2 = hand->cards[1];
	assert(isAce(&card1) || isAce(&card2));

	Card card = card1;
	if (card1.rank == ACE)
		card = card2;

	Int offset = KING - card.rank;
	assert(offset >= 0);

	Int row = strategy->jumpTab[SECTION3].lower + offset;
	assert(row >= strategy->jumpTab[SECTION3].lower && row <= strategy->jumpTab[SECTION3].upper);

	Int col = isAce(upcard) ? 9 : RANK(upcard->rank) - 2;

	Int index = row * 10 + col;

	Play play = strategy->rules[index];

	return play;
}

__host__ __device__ Play doSection2(Hand* hand, Card* upcard, Strategy* strategy) {
	assert(hand->size >= 2 && hand->value >= 4 && hand->value <= 11);

	Int offset = 11 - hand->value;
	assert(offset >= 0);

	Int row = strategy->jumpTab[SECTION2].lower + offset;
	assert(row >= strategy->jumpTab[SECTION2].lower && row <= strategy->jumpTab[SECTION2].upper);

	Int col = isAce(upcard) ? 9 : RANK(upcard->rank) - 2;

	Int index = row * 10 + col;

	Play play = strategy->rules[index];

	// Double-down when more than 2 cards means hit -- see Instructional Services (1983, 2000)
	if (play == DOUBLE_DOWN && hand->size > 2)
		return HIT;

	return play;
}

__host__ __device__ Play doSection1(Hand* hand, Card* upcard, Strategy* strategy) {
	assert(hand->size >= 2 && hand->value >= 12 && hand->value <= 21);

	Int offset = 21 - hand->value;
	assert(offset >= 0);

	Int row = strategy->jumpTab[SECTION1].lower + offset;
	assert(row >= strategy->jumpTab[SECTION1].lower && row <= strategy->jumpTab[SECTION1].upper);

	Int col = isAce(upcard) ? 9 : RANK(upcard->rank) - 2;

	Int index = row * 10 + col;

	Play play = strategy->rules[index];

	// Double-down when more than 2 cards means hit -- see Instructional Services (1983, 2000)
	if (play == DOUBLE_DOWN && hand->size > 2)
		return HIT;

	return play;
}
