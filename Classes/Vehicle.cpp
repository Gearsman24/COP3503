#include "Vehicle.h"

//Default constructor, initializes variables to default values
Vehicle::Vehicle()
{
	make = "COP3503";
	model = "Rust Bucket";
	year = 1900;
	price = 0;
	mileage = 0;
}
//Constructor with parameters
Vehicle::Vehicle(string pMake, string pModel, int pYear, float pPrice, int pMileage)
{
	make = pMake;
	model = pModel;
	year = pYear;
	price = pPrice;
	mileage = pMileage;
}

//Print out the vehicle's details in a single line
void Vehicle::Display()
{
	string strMileage = to_string(mileage);
	cout << fixed << setprecision(2) << GetYearMakeModel() << " $" << GetPrice() << " " << strMileage << endl;
}

//Create and return a string in the form of "YEAR MAKE MODEL"
string Vehicle::GetYearMakeModel()
{
	string response;
	string strYear = to_string(year);

	response = strYear + " " + make + " " + model;

	return response;
}

//Return the price
float Vehicle::GetPrice()
{
	return price;
}