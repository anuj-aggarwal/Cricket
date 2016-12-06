#pragma once
#include <string>


class Credits
{
public:
	Credits(const std::string&);
	~Credits();
private:
	std::string credits;
	bool isLoaded;
public:
	void displayCredits();
};

