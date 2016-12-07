#include "Credits.h"
#include <fstream>
#include <iostream>

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
	credits = "";
	while (inFile.get(ch))
		credits += ch;

	inFile.close();

	isLoaded = true;
}


Credits::~Credits()
{
}


void Credits::displayCredits()
{
	if (!isLoaded) {
		system("cls");
		cout << "Unable to load Credits!!\nPlease fix the files and try again later.....\n\n\n";
		return;
	}

	system("cls");
	cout << credits << "\n\n";
}
