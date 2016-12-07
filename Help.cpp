#include "Help.h"
#include <fstream>
#include <iostream>

using namespace std;

Help::Help(const vector<string>& fileNames)
{
	ifstream inFile;

	for (const string& fileName : fileNames) {

		inFile.open(fileName);

		if (!inFile) {
			isLoaded = false;
			return;
		}

		char ch;
		help.push_back("");
		while (inFile.get(ch))
			help.back() += ch;

		inFile.close();
	}

	isLoaded = true;
}


Help::~Help()
{
}


void Help::displayHelp() const
{
	if (!isLoaded) {
		system("cls");
		cout << "Unable to load Help!!\nPlease fix the files and try again later.....\n\n\n";
		system("pause");
		return;
	}

	for (const string& text : help) {
		system("cls");
		cout << text << "\n\n";
		system("pause");
	}
	system("cls");
}
