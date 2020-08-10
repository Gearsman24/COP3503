#pragma once
#include <string>
#include <iomanip>
#include <iostream>
#include <math.h>
using namespace std;

class Vehicle
{
private:
	 string make;
	 string model;
	 unsigned int year;
	 float price;
	 unsigned int mileage;
public:
	//Constructor
	Vehicle();
	Vehicle(string pMake, string pModel, int pYear, float pPrice, int pMileage);

	//Behaviors
	void Display();
	
	//Accessors
	string GetYearMakeModel();
	float GetPrice();
};