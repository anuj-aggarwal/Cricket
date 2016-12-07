#include "Help.h"

#include <iostream>	// For cout
#include <fstream>	// For ifstream, ofstream


using namespace std;

Help::Help(const vector<string>& fileNames)
{
	ifstream inFile;

	for (const string& fileName : fileNames) {	// Repeat for all files in fileNames

		inFile.open(fileName);

		if (!inFile) {	// Not load even if unable to read one of the files
			isLoaded = false;
			return;
		}

		// Read all contents from current file
		char ch;
		help.push_back("");		// Insert an empty string at the end

		while (inFile.get(ch))
			help.back() += ch;	// Fill the empty string with all the contents of file

		inFile.close();
	}

	isLoaded = true;	// Only if all files are read successfully
}

Help::~Help()
{
}


// Public Member Functions

void Help::displayHelp() const
{
	if (!isLoaded) {	// Display error message if unable to load any of the files

		system("cls");
		cout << "Unable to load Help!!\nPlease fix the files and try again later.....\n\n\n";
		system("pause");
		return;
	}

	for (const string& text : help) {	// Loop for all strings in help
		// Display current string, followed by system pause
		system("cls");
		cout << text << "\n\n";
		system("pause");
	}
	system("cls");
}
