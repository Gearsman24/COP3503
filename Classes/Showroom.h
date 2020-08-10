#pragma once
#include "Vehicle.h"
#include <vector>

class Showroom
{
private:
	string showroomName;
	vector<Vehicle> vehicles;
	unsigned int numVehicles;
	unsigned int showroomCapacity;

public:
	//Default constructor
	Showroom(string pName = "Unnamed Showroom", unsigned int pCapacity = 0);

	//Accessor
	vector<Vehicle> GetVehicleList();

	//Behaviors
	void AddVehicle(Vehicle v);
	void ShowInventory();
	float GetInventoryValue();
};
