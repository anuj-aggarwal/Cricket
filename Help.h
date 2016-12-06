#pragma once
#include <string>
#include <vector>

using namespace std;

class Help
{
public:
	Help(const vector<string>&);
	~Help();

	void displayHelp() const;

private:
	vector<string> help;
	bool isLoaded;

};

