#pragma once
#include <string>
#include <vector>


// Read the help from a series of files
// Store the help, and display when required
class Help
{
public:
	Help(const std::vector<std::string>& fileNames);	// Constructor to open all files
														// and read all data into different strings of help vector
	~Help();

	// Member Functions

	void displayHelp() const;	// Display all strings of help, separated by a system pause


private:

	// Data members
	std::vector<std::string> help;	// Vector to store all the contents of diferent files in different strings
									// Saves overhead of reading from files multiple times

	bool isLoaded;	// false if unable to read from any of the Help files

};