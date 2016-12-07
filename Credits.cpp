#include "Credits.h"
#include <iostream>	// For cout
#include <fstream>	// For ifstream, ofstream

using namespace std;


Credits::Credits(const string& fileName)
{
	ifstream inFile;

	inFile.open(fileName);


	if (!inFile) {
		isLoaded = false;
		return;
	}


	char ch;
	credits = "";	// Set credits to empty string
	while (inFile.get(ch))
		credits += ch;	// Read the contents of file into the string


	inFile.close();

	isLoaded = true;
}

Credits::~Credits()
{
}


// Public Member Functions

void Credits::displayCredits()
{
	if (!isLoaded) {	// Displays error message if unable to read from file

		system("cls");
		cout << "Unable to load Credits!!\nPlease fix the files and try again later.....\n\n\n";
		return;
	}

	system("cls");
	cout << credits << "\n\n";
}
