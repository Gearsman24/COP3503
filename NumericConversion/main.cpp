#include <fstream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <map>
#include "Color.h"
using namespace std;

void ReadFile(const char* filename, map<string, Color>& colors);
void PrintColors(const map<string, Color>& colors);
void PrintColor(const Color& color);
void SearchForColor(map<string, Color>& colors);

int main()
{
	cout << "1-6: Load colors1/2/3/4/5/6.txt" << endl;
	cout << "7. Load all 6 files" << endl;
	int choice;
	cin >> choice;

	map<string, Color> colors;
	if (choice >= 1 && choice <= 6)
	{
		string file = "colors" + to_string(choice) + ".txt";
		ReadFile(file.c_str(), colors);
	}
	else if (choice == 7)
	{
		for (int i = 1; i <= 6; i++)
		{
			string file = "colors" + to_string(i) + ".txt";
			ReadFile(file.c_str(), colors);
		}

	}

	// Secondary menu
	cout << "1. Show all colors" << endl;
	cout << "2. Search for a color" << endl;
	cin >> choice;

	if (choice == 1)
		PrintColors(colors);
	else if (choice == 2)
		SearchForColor(colors);
	return 0;
}

void ReadFile(const char* filename, map<string, Color>& colors)
{
	// TODO: Read the file, create and store some Color objects
	Color newColor;
	string data;
	string key;

	ifstream file;
	file.open(filename);

	while (!file.eof())
	{
		getline(file, data);
		key = data;

		int index = key.find(" ");
		key = key.substr(0, index);
		newColor.SetName(key.c_str());

		data = data.substr(index + 1);
		newColor.SetValue(stoi(data));

		colors.emplace(key, newColor);
	}

}
void PrintColors(const map<string, Color>& colors)
{
	// TODO: iterate through all entries in the map and print each color, one at a time
	int colorCount = 0;
	map<string, Color>::const_iterator i;

	for (i = colors.begin(); i != colors.end(); i++)
	{
		PrintColor(i->second);
		colorCount++;
	}

	// Print out the color count afterward
	cout << "Number of colors: " << colorCount << endl;

}
void PrintColor(const Color& color)
{
	cout << left << setw(20) << color.GetName();
	cout << right << setw(10) << color.GetHexValue();
	cout << "\t\t" << (int)color.GetR() << "," << (int)color.GetG() << "," << (int)color.GetB() << endl;
}
void SearchForColor(map<string, Color>& colors)
{
	// TODO: Get some input, check if that key exists, then print out the color (or an error message)
	string userColor;
	cin.ignore();
	getline(cin, userColor);

	map<string, Color>::iterator i = colors.find(userColor);
	if (i != colors.end())
	{
		cout << left << setw(20) << i->first;
		cout << right << setw(10) << i->second.GetHexValue();
		cout << "\t\t" << (int)i->second.GetR() << "," << (int)i->second.GetG() << "," << (int)i->second.GetB() << endl;
	}
	else
	{
		cout << userColor << " not found!" << endl;
	}
}
