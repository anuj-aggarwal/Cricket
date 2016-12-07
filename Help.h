#pragma once
#include <string>
#include <vector>


class Help
{
public:
	Help(const std::vector<std::string>& fileNames);
	~Help();

	void displayHelp() const;

private:
	std::vector<std::string> help;
	bool isLoaded;

};

