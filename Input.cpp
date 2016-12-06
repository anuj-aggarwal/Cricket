#include "Input.h"
#include <iostream>
#include <string>

using namespace std;

void wait(string ch)
{
	cin.clear();
	cout << "\nPress " << ch << " to continue: ";
	string c;
	cin >> c;
	while (c != ch) {
		cout << "\nPress " << ch << " to continue: ";
		cin >> c;
	}
}
void wait()
{
	cin.clear();
	cout << "\nPress any key to continue: ";
	string ch;
	cin >> ch;

}
int getNum(const string& prompt)
{
	cout << endl << prompt;
	int n;
	cin >> n;

	while (!cin) {
		if (cin.eof())
			throw runtime_error("End of Input received!!\n");
		cin.clear();
		string ch;
		cout << "\nOOps, a number is required!!Please try again.....\n";
		getline(cin, ch);
		cout << endl << prompt;
		cin >> n;

	}

	return n;
}
int getPositiveNum(const string& prompt)
{
	int n;
	n = getNum(prompt);
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
	getline(cin, s);

	while (s == "")
		getline(cin, s);

	if (!cin)
		throw runtime_error("End of Input received!!\n");

	return s;
}
char getChar(const string& prompt)
{
	cout << prompt;
	char ch;
	cin >> ch;

	if (!cin) {
		throw runtime_error("End of Input received!!\n");
	}

	return ch;
}