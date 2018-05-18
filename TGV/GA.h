#pragma once
#include "Strategy.h"

#define MUTATION_RATE 0.015
#define TOURNAMENT_SIZE 5

Strategy cross(Strategy* mother, Strategy* father);
Strategy* getFittest(Strategy** individuals);
