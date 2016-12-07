#pragma once
#include <string>


class Credits
{
public:
	Credits(const std::string& fileName);
	~Credits();

	void displayCredits();

private:
	std::string credits;
	bool isLoaded;

};

