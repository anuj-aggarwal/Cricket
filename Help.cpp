#include "Help.h"
#include <fstream>
#include <iostream>

using namespace std;

Help::Help(const vector<string>& fileNames)
{
	ifstream fin;

	for (const string& name : fileNames) {
		
		fin.open(name);

		if (!fin) {
			isLoaded = false;
			return;
		}

		char ch;
		help.push_back("");
		while (fin.get(ch))
			help.back() += ch;
		
		fin.close();
	}

	isLoaded = true;
}


Help::~Help()
{
}


void Help::displayHelp()
{
	if (!isLoaded) {
		system("cls");
		cout << "Unable to load Help!!\nPlease fix the files and try again later.....\n\n\n";
		system("pause");
		return;
	}

	for (string& text : help) {
		system("cls");
		cout << text << "\n\n";
		system("pause");
	}
}
