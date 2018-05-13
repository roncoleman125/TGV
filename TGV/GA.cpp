#include "GA.h" 
#include "../Bj/Strategy.h"
#include "Population.h"

Strategy cross(Strategy* a, Strategy* b) {
	Strategy c = Strategy_();

	for (int index = 0; index < NUMBER_RULES; index++) {
		int lottery = random(0, 1);

		if (lottery == 0)
			c.rules[index] = a->rules[index];
		else
			c.rules[index] = b->rules[index];
	}

	return c;
}

void mutate(Strategy* individual) {
	Play plays[] = { STAY, HIT, DOUBLE_DOWN, SPLIT };

	Int numPlays = sizeof(plays) / sizeof(Int);

	for (int index = 0; index < NUMBER_RULES; index++) {

		float lottery = random();

		if (lottery > MUTATION_RATE)
			continue;

		Int ran = random(0, numPlays - 1);

		Play allele = plays[ran];

		individual->rules[index] = allele;
	}
}

Strategy* tournamentSelect(Population* population) {
	Strategy* tournament[TOURNAMENT_SIZE];

	for (int index = 0; index < TOURNAMENT_SIZE; index++) {
		int lottery = random(0, POPULATION_SIZE);

		tournament[index] = &population->individuals[lottery];
	}

	Strategy* winner = getFittest(tournament);

	return winner;
}

Strategy* getFittest(Strategy** individuals) {
	Strategy* fittest = individuals[0];

	for (int index = 1; index < TOURNAMENT_SIZE; index++) {
		if (individuals[index]->pl > fittest->pl)
			fittest = individuals[index];
	}

	return fittest;
}

Strategy* getFittest(Population* population) {
	Strategy* fittest = &population->individuals[0];

	for (Int index = 1; index < population->size; index++)
		if (population->individuals[index].pl > fittest->pl)
			fittest = &population->individuals[index];

	return fittest;
}

Population evolve(Population* oldPopulation) {
	Population newPopulation = Population_();

	if (ELITIST)
		newPopulation.individuals[0] = *getFittest(oldPopulation);

	for (int index = ELITIST ? 1 : 0; index < POPULATION_SIZE; index++) {
		Strategy* mother = tournamentSelect(oldPopulation);

		Strategy* father = tournamentSelect(oldPopulation);

		Strategy child = cross(mother, father);

		newPopulation.individuals[index] = child;
	}

	return newPopulation;
}