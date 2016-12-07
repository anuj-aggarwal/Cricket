#include "Input.h"

#include <iostream>	// For cin, getline()

using namespace std;

int getNum(const string& prompt)
{
	cout << endl << prompt;
	
	int n;
	cin >> n;

	while (!cin) {		// Repeat untill cin's state is not good

		if (cin.eof())
			throw runtime_error("End of Input received!!\n");
		
		cin.clear();	// Set state of cin to good

		string ch;
		cout << "\nOOps, a number is required!!Please try again.....\n";

		getline(cin, ch);	// Clear the already present characters untill '\n' is reached
		
		// Try to read a number again
		cout << endl << prompt;
		cin >> n;

	}

	return n;
}
int getPositiveNum(const string& prompt)
{
	int n;
	n = getNum(prompt);	// get a number from cin

	while (n < 0) {
		cout << "\nSorry, positive number expected(>=0)!!Please try again.....\n";
		
		n = getNum(prompt);
	}
	return n;
}
string getString(const string& prompt)
{
	cout << prompt;
	string s;
	getline(cin, s);	// fails if an unread '\n' is encountered

	while (s == "")	// Untill a string is read and not because of unread '\n'
		getline(cin, s);

	if (!cin)	// Only if End of Input is reached
		throw runtime_error("End of Input received!!\n");

	return s;
}
char getChar(const string& prompt)
{
	cout << prompt;
	char ch;
	cin >> ch;

	if (!cin) {		// Only if an End of Input is reached
		throw runtime_error("End of Input received!!\n");
	}

	return ch;
}