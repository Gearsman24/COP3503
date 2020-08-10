#pragma once
#include <iostream>

class Color
{
	std::string colorName;
	int colorValue;

	unsigned char R;
	unsigned char G;
	unsigned char B;

public:
	//Given an integer value, convert it to RGB and Hex values
	void SetValue(int value);
	void SetName(const char* name);

	//Accessors
	unsigned char GetR() const;
	unsigned char GetG() const;
	unsigned char GetB() const;

	std::string GetHexValue() const;
	std::string GetName() const;

	char GetLetter(int hex) const;
	char GetNumber(int hex) const;

};


