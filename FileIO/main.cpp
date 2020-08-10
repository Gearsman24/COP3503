#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

//Opens a file
void openFile(ifstream& file, int fileOption)
{
	string fileName = "lego" + to_string(fileOption) + ".csv";
	file.open(fileName);
}

//Loads data from file
void loadData(ifstream& file, string& data, vector<string>& dataSet, int num)
{
	if (num != 1)
	{
		getline(file, data, ',');
		dataSet.push_back(data);
	}
	//Last item in row
	else
	{
		file >> data;
		dataSet.push_back(data);
	}

}

void printSetData(int i, vector<string> names, vector<string> numbers, vector<string> themes, vector<string> prices, vector<string> minifigs, vector<string> pieces)
{
	cout << "Name: " << names.at(i) << endl;
	cout << "Number: " << numbers.at(i) << endl;
	cout << "Theme: " << themes.at(i) << endl;
	cout << "Price: $" << stod(prices.at(i)) << endl;
	cout << "Minifigures: " << minifigs.at(i) << endl;
	cout << "Piece count: " << pieces.at(i) << endl;
}

void printMatch(vector<string> matchSet, string keyword, vector<string> numbers, vector<string> prices, vector<string> names)
{
	bool match = false;
	for (unsigned int i = 0; i < matchSet.size(); i++)
	{
		if (matchSet.at(i).find(keyword) != string::npos) //npos indicates no matches
		{
			match = true;
			break;
		}
	}
	if (match == false)
	{
		cout << "No sets found matching that search term" << endl;
	}
	else
	{
		cout << "Sets matching \"" << keyword << "\":" << endl;
	}

	for (unsigned int i = 0; i < matchSet.size(); i++)
	{
		if (matchSet.at(i).find(keyword) != string::npos) //npos indicates no matches
		{
			cout << numbers.at(i) << " " << names.at(i) << " $" << stod(prices.at(i)) << endl;
		}
	}

}

int getHighestAmount(vector<string> amountSet)
{
	double highestAmount = 0.0;
	int index = 0;
	for (unsigned int i = 0; i < amountSet.size(); i++)
	{
		if (stod(amountSet.at(i)) > highestAmount)
		{
			highestAmount = stod(amountSet.at(i));
			index = i;
		}
	}

	return index;
}

int getLowestAmount(vector<string> amountSet)
{
	double lowestAmount = 1000000;
	int index = 0;
	for (unsigned int i = 0; i < amountSet.size(); i++)
	{
		if (stod(amountSet.at(i)) < lowestAmount)
		{
			lowestAmount = stod(amountSet.at(i));
			index = i;
		}
	}

	return index;
}

double getAverage(vector<string> averageSet)
{
	double average = 0.0;
	double total = 0.0;
	int numSets = 0;
	for (unsigned int i = 0; i < averageSet.size(); i++)
	{
		total = total + stod(averageSet.at(i));
		numSets++;
	}
	if (numSets != 0)
	{
		average = total / numSets;
	}

	return average;
}


int main()
{
	cout << std::fixed << setprecision(2);
	cout << "Which file(s) to open?\n";
	cout << "1. lego1.csv" << endl;
	cout << "2. lego2.csv" << endl;
	cout << "3. lego3.csv" << endl;
	cout << "4. All 3 files" << endl;
	int option;
	cin >> option;


	/*======= Load data from file(s) =======*/

	vector<string> setNumbers;
	vector<string> setThemes;
	vector<string> setNames;
	vector<string> setMinifigs;
	vector<string> setPieces;
	vector<string> setPrices;
	unsigned int numberOfSets = 0;

	ifstream inFile;
	//Data from files
	//Data from all files
	
	for (int i = 1; i <= option; i++)
	{
		if (option < 4)
		{
			//Open File Chosen
			openFile(inFile, option);
		}
		else
		{
			//Open All Files
			openFile(inFile, i);
		}

		//Skips the first line with categories
		string line;
		getline(inFile, line);
		//Go through each line and load corresponding data
		while (!inFile.eof()) //In .csv a ',' separates columns
		{
			loadData(inFile, line, setNumbers, 0);
			loadData(inFile, line, setThemes, 0);
			loadData(inFile, line, setNames, 0);
			loadData(inFile, line, setMinifigs, 0);
			loadData(inFile, line, setPieces, 0);
			loadData(inFile, line, setPrices, 1); //Last item in row

			numberOfSets++;
		}

		inFile.close();

		//If only a single file is chosen
		if (option != 4)
		{
			break;
		}
	}
	
	cout << "1. Most Expensive set" << endl;
	cout << "2. Largest piece count" << endl;
	cout << "3. Search for set name containing..." << endl;
	cout << "4. Search themes..." << endl;
	cout << "5. Part count information" << endl;
	cout << "6. Price information" << endl;
	cout << "7. Minifigure information" << endl;
	cout << "8. If you bought one of everything..." << endl;
	cout << "0. Exit" << endl;

	int choice;
	cin >> choice;
	cin.get();  // Clear newline character for any later input

	/*======= Print out how many sets were loaded =======*/
	cout << "Total number of sets: " << numberOfSets << endl << endl;

	/*======= Based on the choice, execute the appropriate task and show the results =======*/

	
	//1. Find most expensive set
	if (choice == 1)
	{
		int mostExpensiveIndex = getHighestAmount(setPrices);
		cout << "The most expensive set is:" << endl;
		printSetData(mostExpensiveIndex, setNames, setNumbers, setThemes, setPrices, setMinifigs, setPieces);
	}
	//2. Find largest piece count set
	else if (choice == 2)
	{
		int pieceIndex = getHighestAmount(setPieces);
		cout << "The set with the highest parts count:" << endl;
		printSetData(pieceIndex, setNames, setNumbers, setThemes, setPrices, setMinifigs, setPieces);
	}
	//3. Find sets with keyword in NAME
	else if (choice == 3)
	{
		string userKeyword;
		getline(cin >> ws, userKeyword);
		printMatch(setNames, userKeyword, setNumbers, setPrices, setNames);
	}
	//4. Find sets with keyword in THEME
	else if (choice == 4)
	{
		string userKeyword;
		getline(cin >> ws, userKeyword);
		printMatch(setThemes, userKeyword, setNumbers, setPrices, setNames);
	}
	//5. Get part count information
	else if (choice == 5)
	{
		int averageParts = (int) getAverage(setPieces);
		cout << "Average part count for " << numberOfSets << " sets: " << averageParts;
	}
	//6. Get price information
	else if (choice == 6)
	{
		double averagePrice = getAverage(setPrices);
		cout << std::fixed << setprecision(2) << "Average price for " << numberOfSets << " sets: $" << averagePrice << endl << endl;
		int minPriceIndex = getLowestAmount(setPrices);
		cout << "Least expensive set:" << endl;
		printSetData(minPriceIndex, setNames, setNumbers, setThemes, setPrices, setMinifigs, setPieces);
		cout << endl << "Most expensive set:" << endl;
		int maxPriceIndex = getHighestAmount(setPrices);
		printSetData(maxPriceIndex, setNames, setNumbers, setThemes, setPrices, setMinifigs, setPieces);
	}
	//7. Get minifigure information
	else if (choice == 7)
	{
		int averageMinifigs = (int) getAverage(setMinifigs);
		cout << "Average number of minifigures: " << averageMinifigs << endl;
		int maxMinifigIndex = getHighestAmount(setMinifigs);
		cout << "Set with the most minifigures:" << endl;
		printSetData(maxMinifigIndex, setNames, setNumbers, setThemes, setPrices, setMinifigs, setPieces);
	}
	//8. If you bought one of everything
	else if (choice == 8)
	{
		cout << "If you bought one of everything..." << endl;
		double maxPrice = 0.0;
		int maxPieces = 0;
		int maxMinifigs = 0;
		for (unsigned int i = 0; i < setNumbers.size(); i++)
		{
			maxPrice = maxPrice + stod(setPrices.at(i));
			maxPieces = maxPieces + stoi(setPieces.at(i));
			maxMinifigs = maxMinifigs + stoi(setMinifigs.at(i));
		}

		cout << "It would cost: $" << maxPrice << endl;
		cout << "You would have " << maxPieces << " pieces in your collection" << endl;
		cout << "You would have an army of " << maxMinifigs << " minifigures!" << endl;
	}
	//0. Exit
	if (choice == 0)
	{
		return 0;
	}

	return 0;
}