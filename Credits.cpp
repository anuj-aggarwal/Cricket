#include "Credits.h"
#include <fstream>
#include <iostream>

using namespace std;


Credits::Credits(const string& name)
{
	ifstream fin;

	fin.open(name);

	if (!fin) {
		isLoaded = false;
		return;
	}

	char ch;
	credits = "";
	while (fin.get(ch))
		credits += ch;

	fin.close();

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
