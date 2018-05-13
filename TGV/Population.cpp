#include "Population.h"

Population Population_() {
	Population population = { POPULATION_SIZE, 0,{ Strategy_() } };

	return population;
}