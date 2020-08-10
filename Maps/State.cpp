#include "State.h"

std::string State::getName()
{
	return name;
}
std::string State::getPerCapitaIncome()
{
	return perCapitaIncome;
}
std::string State::getPopulation()
{
	return population;
}
std::string State::getHouseIncome()
{
	return houseIncome;
}
std::string State::getNumHouseholds()
{
	return numHouseholds;
}

void State::setName(std::string pName)
{
	name = pName;
}
void State::setPerCapitaIncome(std::string PCI)
{
	perCapitaIncome = PCI;
}
void State::setPopulation(std::string pPopulation)
{ population = pPopulation; 
}
void State::setHouseIncome(std::string pHouseIncome)
{
	houseIncome = pHouseIncome;
}
void State::setNumHouseholds(std::string pNumHouseholds)
{
	numHouseholds = pNumHouseholds;
}