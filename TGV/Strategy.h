#pragma once
#include "Utils.h"
#include "Hand.h"

typedef enum { NO_PLAY = 0, STAY = 'S', HIT = 'H', DOUBLE_DOWN = 'D', SPLIT = 'P' } Play;

#define NUMBER_RULES (10*43)
#define SECTION1 0
#define SECTION2 1
#define SECTION3 2
#define SECTION4 3
#define S STAY
#define H HIT
#define D DOUBLE_DOWN
#define P SPLIT
#define X NO_PLAY

typedef struct {
	Int lower, upper;
} Entry;

typedef struct {
	float pl;
	Play rules[NUMBER_RULES];
	Entry jumpTab[4];
} Strategy;


__host__ __device__ Strategy BasicStrategy_();
__host__ __device__ Strategy Strategy_();
__host__ __device__ Play doSection4(Hand* hand, Card* upcard, Strategy* strategy);
__host__ __device__ Play doSection3(Hand* hand, Card* upcard, Strategy* strategy);
__host__ __device__ Play doSection2(Hand* hand, Card* upcard, Strategy* strategy);
__host__ __device__ Play doSection1(Hand* hand, Card* upcard, Strategy* strategy);
