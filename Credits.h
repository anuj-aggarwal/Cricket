#pragma once
#include <string>

using namespace std;

class Credits
{
public:
	Credits(const string&);
	~Credits();
private:
	string credits;
	bool isLoaded;
public:
	void displayCredits();
};

