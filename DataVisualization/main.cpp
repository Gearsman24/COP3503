#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

int main()
{
	//Get some input for the title, column header #1, and column header #2
	//getline(istream&, string&) gets input from strings including spaces
	string title;
	cout << "Enter a title for the data:" << endl;
	getline(cin, title);
	cout << "You entered: " << title << endl << endl;

	string firstHeader;
	cout << "Enter the column 1 header:" << endl;
	getline(cin, firstHeader);
	cout << "You entered: " << firstHeader << endl << endl;

	string secondHeader;
	cout << "Enter the column 2 header:" << endl;
	getline(cin, secondHeader);
	cout << "You entered: " << secondHeader << endl;


	string input;
	vector<string> authors;
	vector<int> novels;
	while (input != "-1")
	{
		//Get input for a string
		cout << endl << "Enter a data point (-1 to stop input):" << endl;
		getline(cin, input);

		//Until the user types "-1"
		if (input == "-1")
		{
			cout << endl;
			continue;
		}

		//Exception if entry has no comma
		int firstComma = input.find(',');
		if (firstComma < 0)
		{
			cout << "Error: No comma in string." << endl;
			continue;
		}

		//Exception if entry has too many commas
		int nextComma = input.find(",", firstComma + 1);
		if (nextComma > 0)
		{
			cout << "Error: Too many commas in input." << endl;
			continue;
		}

		//Split
		string tempAuthor = input.substr(0, firstComma);
		string tempNovel = input.substr(firstComma + 2, input.size());

		//Exception if entry after the comma is not an integer
		//Note: I have no idea why but I could never get the try/catch option to work
		bool isDigit = true;
		for (int i = 0; i < (int) tempNovel.size(); i++)
		{
			if (!isdigit(tempNovel.at(i)))
			{
				isDigit = false;
				break;
			}
		}
		if (!isDigit)
		{
			cout << "Error: Comma not followed by an integer." << endl;
			continue;
		}
		
		//Store separate pieces
		authors.push_back(tempAuthor);
		novels.push_back(stoi(tempNovel));

		//Print response
		cout << "Data string: " << tempAuthor << endl;
		cout << "Data integer: " << tempNovel << endl;
	}

	//Print out data in table format
	/*
	setw(int) specifies how many characters the next output should be
	Title right justified value 33
	Column 1 left justified value 20
	Column 2 right justified value 23
	*/
	cout << setw(33) << right << title << endl;
	cout << setw(20) << left << firstHeader << "|";
	cout << setw(23) << right << secondHeader << endl;
	cout << "--------------------------------------------" << endl;

	for (int i = 0; i < (int) novels.size(); i++)
	{
		cout << setw(20) << left << authors.at(i) << "|";
		cout << setw(23) << right << novels.at(i) << endl;
	}

	//Print out data in chart format
	/*
	Names right justified value 20
	*/
	cout << endl;
	for (int i = 0; i < (int) novels.size(); i++)
	{
		cout << setw(20) << right << authors.at(i) << " ";
		for (int j = 0; j < novels.at(i); j++)
		{
			cout << "*";
		}
		cout << endl;
	}

	return 0;
}