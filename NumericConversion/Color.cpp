#include "Color.h"

void Color::SetName(const char* name)
{
	colorName = name;
}
void Color::SetValue(int value)
{
	colorValue = value;

	R = colorValue >> 16;
	G = colorValue >> 8;
	B = colorValue;
}

std::string Color::GetName() const
{
	return colorName;
}
std::string Color::GetHexValue() const
{
	std::string hexValue = "0x";

	char color = R / 16;
	char remainder = R % 16;

	//Red
	if ((int)color > 9)
		color = GetLetter((int)color);
	else
		color = GetNumber((int)color);
	hexValue += color;

	if ((int)remainder > 9)
		remainder = GetLetter((int)remainder);
	else
		remainder = GetNumber((int)remainder);
	hexValue += remainder;

	//Green
	color = G / 16;
	if ((int)color > 9)
		color = GetLetter((int)color);
	else
		color = GetNumber((int)color);
	hexValue += color;

	remainder = G % 16;
	if ((int)remainder > 9)
		remainder = GetLetter((int)remainder);
	else
		remainder = GetNumber((int)remainder);
	hexValue += remainder;

	//Blue
	color = B / 16;
	if ((int)color > 9)
		color = GetLetter((int)color);
	else
		color = GetNumber((int)color);
	hexValue += color;

	remainder = B % 16;
	if ((int)remainder > 9)
		remainder = GetLetter((int)remainder);
	else
		remainder = GetNumber((int)remainder);
	hexValue += remainder;
		
	return hexValue;
}
char Color::GetLetter(int hex) const
{
	switch (hex)
	{
	case 10:
		return 'A';
	case 11:
		return 'B';
	case 12:
		return 'C';
	case 13:
		return 'D';
	case 14:
		return 'E';
	case 15:
		return 'F';
	default:
		return ' ';
	}
}
char Color::GetNumber(int hex) const
{
	switch (hex)
	{
	case 0:
		return '0';
	case 1:
		return '1';
	case 2:
		return '2';
	case 3:
		return '3';
	case 4:
		return '4';
	case 5:
		return '5';
	case 6:
		return '6';
	case 7:
		return '7';
	case 8:
		return '8';
	case 9:
		return '9';
	default:
		return ' ';
	}
}

unsigned char Color::GetR() const
{
	return R;
}
unsigned char Color::GetG() const
{
	return G;
}
unsigned char Color::GetB() const
{
	return B;
}