#include "Showroom.h"
#include <iostream>

//Default Constructor
Showroom::Showroom(string pName, unsigned int pCapacity)
{
	showroomName = pName;
	showroomCapacity = pCapacity;
	numVehicles = 0;
}

//Accessor
vector<Vehicle> Showroom::GetVehicleList()
{
	return vehicles;
}

//Behaviors
void Showroom::AddVehicle(Vehicle v)
{
	if (numVehicles != showroomCapacity)
	{
		vehicles.push_back(v);
		numVehicles++;
	}
	else
	{
		cout << "Showroom is full! Cannot add " << v.GetYearMakeModel() << endl;
	}
}

void Showroom::ShowInventory()
{
	if (vehicles.empty())
	{
		cout << showroomName << " is empty!" << endl;
	}
	else
	{
		cout << "Vehicles in " << showroomName << endl;
		for (int i = 0; i < (int)vehicles.size(); i++)
		{
			vehicles.at(i).Display();
		}
	}

}

float Showroom::GetInventoryValue()
{
	float response = 0;

	for (int i = 0; i < (int)vehicles.size(); i++)
	{
		response += vehicles.at(i).GetPrice();
	}

	return response;
}