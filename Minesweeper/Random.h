#pragma once
#include <random>

/* From "Project3 - Helper classes (Random numbers)*/
class Random
{
	static std::mt19937 random;
public:
	static int randNum(int min, int max);
};