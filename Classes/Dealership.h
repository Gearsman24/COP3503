#pragma once
#include "Showroom.h"

class Dealership
{
private:
	string dealershipName;
	vector<Showroom> showrooms;
	unsigned int numShowrooms;
	unsigned int dealershipCapacity;

public:
	//Constructor
	Dealership(string pName = "Generic Dealership", unsigned int capacity = 0);

	//Behaviors
	void AddShowroom(Showroom s);
	float GetAveragePrice();
	void ShowInventory();
};