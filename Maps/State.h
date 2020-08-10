#pragma once
#include <iostream>

class State
{
	std::string name;
	std::string perCapitaIncome;
	std::string population;
	std::string houseIncome;
	std::string numHouseholds;

public: 
	std::string getName();
	std::string getPerCapitaIncome();
	std::string getPopulation();
	std::string getHouseIncome();
	std::string getNumHouseholds();

	void setName(std::string pName);
	void setPerCapitaIncome(std::string PCI);
	void setPopulation(std::string pPopulation);
	void setHouseIncome(std::string pHouseIncome);
	void setNumHouseholds(std::string pNumHouseholds);

};