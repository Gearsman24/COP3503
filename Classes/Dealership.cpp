#include "Dealership.h"

//Constructor
Dealership::Dealership(string pName, unsigned int pCapacity)
{
	dealershipName = pName;
	dealershipCapacity = pCapacity;
	numShowrooms = 0;
}

//Behaviors
void Dealership::AddShowroom(Showroom s)
{
	if (numShowrooms != dealershipCapacity)
	{
		showrooms.push_back(s);
		numShowrooms++;
	}
	else
	{
		cout << "Dealership is full, can't add another showroom!" << endl;
	}
}

float Dealership::GetAveragePrice()
{
	float average = 0;
	float totalValue = 0;
	unsigned int numValues = 0;

	for (int i = 0; i < (int)showrooms.size(); i++)
	{
		vector<Vehicle> vehicles = showrooms.at(i).GetVehicleList();
		for (int j = 0; j < (int) vehicles.size(); j++)
		{
			totalValue = totalValue + vehicles.at(j).GetPrice();
			numValues++;
		}
	}

	if (numValues != 0)
	{
		average = totalValue / numValues;
	}
	else
	{

	}

	return average;
}

void Dealership::ShowInventory()
{
	
	if (showrooms.empty())
	{
		cout << dealershipName << " is empty!" << endl;
	}
	else
	{
		for (int i = 0; i < (int)showrooms.size(); i++)
		{
			showrooms.at(i).ShowInventory();
			cout << endl;
		}
	}
	cout << fixed << setprecision(2) << "Average car price: $" << GetAveragePrice();
}

