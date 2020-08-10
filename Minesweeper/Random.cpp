#include "Random.h"
#include <ctime>

/* From "Project3 - Helper classes (Random numbers)*/
std::mt19937 Random::random(time(0));
int Random::randNum(int min, int max)
{
	std::uniform_int_distribution<int> dist(min, max);
	return dist(random);
}