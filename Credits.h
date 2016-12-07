#pragma once
#include <string>


class Credits
{
public:
	Credits(const std::string&);
	~Credits();

	void displayCredits();

private:
	std::string credits;
	bool isLoaded;

};

