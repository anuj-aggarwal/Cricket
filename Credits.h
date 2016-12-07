#pragma once
#include <string>


// Read the credits from a file,
// store them in a string, display when asked to
class Credits
{
public:
	Credits(const std::string& fileName);	// Constructor to read all the contents from file: fileName
	~Credits();


	// MEMBER FUNCTIONS

	void displayCredits();	// Displays all the credits when called, followed by a system pause
							// Displays error message if unable to read from the file

private:
	// DATA MEMBERS

	std::string credits;	// Stores the contents of the file to prevent reading from file multiple times

	bool isLoaded;	// true if successfully read all contents of the file
					// false if unable to read from the file

};

