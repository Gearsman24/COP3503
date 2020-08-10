#include <map>
#include <random>
#include <ctime>
#include <fstream>
#include <string>
#include "State.h"
using namespace std;

//An "engine" for generating random numbers
mt19937 random_mt;

//Using that engine generate a random number between two parameters (inclusively)
int Random(int min, int max)
{
	uniform_int_distribution<int> dist(min, max);
	return dist(random_mt);
}

/* FUNCTIONS */
void RollDice(int numberOfRolls, int numberOfSides)
{
	map<int, int> rolls;

	for (int i = 1; i <= numberOfRolls; i++)
	{
		int rand = Random(1, numberOfSides);
		rolls[rand]++;
	}

	for (int i = 1; i <= numberOfSides; i++)
		cout << i << ": " << rolls[i] << endl;
}

void loadData(ifstream& file, State& state, int num)
{
	string data;
	
	if (num != 4)
		getline(file, data, ',');
	else
		file >> data;

	switch (num)
	{
	case 0:
		data.erase(remove(data.begin(), data.end(), '\n'), data.end()); // '\n' was messing up find() function
		state.setName(data);
		break;
	case 1:
		state.setPerCapitaIncome(data);
		break;
	case 2:
		state.setPopulation(data);
		break;
	case 3:
		state.setHouseIncome(data);
		break;
	case 4:
		state.setNumHouseholds(data);
		
	}
}

int main()
{
	cout << "1. Random Numbers\n";
	cout << "2. State Info\n";

	int option;
	cin >> option;

	if (option == 1)
	{
		int randomSeed;
		cout << "Random seed value: ";
		cin >> randomSeed;
		random_mt.seed(randomSeed);

		cout << "Number of times to roll the die: ";
		// user input
		int numRolls;
		cin >> numRolls;

		cout << "Number of sides on this die: ";
		// user input
		int numSides;
		cin >> numSides;

		// Roll Dice
		cout << endl;
		RollDice(numRolls, numSides);
	}
	else if (option == 2)
	{
		map<string, State> states;

		{
			// Load the states
			ifstream file;
			file.open("states.csv");

			string line;
			getline(file, line); //Skip header

			State state;
			while (!file.eof())
			{
				for (int i = 0; i < 5; i++)
					loadData(file, state, i);

				
				states.emplace(state.getName(), state);
			}
		}

		// Get input for option 1 (show all states) or 2 (do a search for a particular state)
		cout << "1. Print all states\n";
		cout << "2. Search for a state\n";

		cin >> option;

		if (option == 1)
		{
			map<string, State>::iterator i;
			for (i = states.begin(); i != states.end(); i++)
			{
				cout << i->second.getName() << endl;
				cout << "Population: " << i->second.getPopulation() << endl;
				cout << "Per Capita Income: " << i->second.getPerCapitaIncome() << endl;
				cout << "Median Household Income: " << i->second.getHouseIncome() << endl;
				cout << "Number of Households: " << i->second.getNumHouseholds() << endl;
			}
		}
		else if (option == 2)
		{
			string userState;
			cin.ignore();
			getline(cin, userState);

			map<string, State>::iterator i;
			
			i = states.find(userState);
			if (i != states.end())
			{
				cout << i->second.getName() << endl;
				cout << "Population: " << i->second.getPopulation() << endl;
				cout << "Per Capita Income: " << i->second.getPerCapitaIncome() << endl;
				cout << "Median Household Income: " << i->second.getHouseIncome() << endl;
				cout << "Number of Households: " << i->second.getNumHouseholds() << endl;
			}
			else
			{
				cout << "No match found for " << userState << endl;
			}
		}

	}

	return 0;
}