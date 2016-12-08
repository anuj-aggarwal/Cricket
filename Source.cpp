#include <iostream>	// For cout
#include <string>	// Just for completion of Documentation, Not required, already included in Team.h
#include <vector>	// Just for completion of Documentation, Not required, already included in Team.h

#include "Game.h"
#include "Database.h"
#include "Team.h"	// Just for completion of Documentation, Not required, already included in Database.h
#include "Help.h"
#include "Credits.h"
#include "Input.h"


using namespace std;


// GLOBAL VARIABLES

// Location that stores the Game Data
const string fileName = "../Cricket/Details.txt";
// Location of files containing different displays of HELP
const vector<string> helpFileNames = { "../Cricket/Help/Help.txt", "../Cricket/Help/DatabaseHelp.txt", "../Cricket/Help/RulesHelp.txt", "../Cricket/Help/GamePlayHelp.txt" };
// Location of file containing Credits
const string creditsFileName = "../Cricket/Credits.txt";


// FUNCTION DEFINITIONS
int displayMenu();	// Displays the Main Menu and asks the User's choice
					// Calls getNum() to ensure a number as input



// MAIN
// Program starts from here
int main()
try {

	// Create a Database for storing all data
	Database database(fileName);

	// Creating a local Database in teams
	vector<Team>& teams = database.getTeams();

	// Create a new Game
	Game game(teams);

	// Load Help and Credits from the specified Files
	Help help(helpFileNames);
	Credits credits(creditsFileName);


	// MAIN MENU Display and Calling functions

	char ch;
	do {
		int choice;
		choice = displayMenu();

		switch (choice) {

		case 1:
			// PLAY
			game.play();
			break;

		case 2:
			// DATABASE
			database.menu();
			break;

		case 3:
			// HELP
			help.displayHelp();
			break;

		case 4:
			// CREDITS
			credits.displayCredits();
			break;

		case 5:
			// EXIT
			cout << "\n****** THE END ******\n\n\n";
			system("pause");
			return 0;

		default:
			// Invalid Input
			cout << "Wrong choice!!\n";
			break;
		}

		// Ask if User wants to run the program again
		ch = getChar("\nDo you want to go to MAIN MENU(y/n)?:\n");

	} while (ch == 'y' || ch == 'Y');


	system("pause");
	return 0;
}
catch (exception& e) {
	cerr << endl << e.what() << endl;
	system("pause");
	return 1;
}
catch (...) {
	cerr << "OOps, Unknown error!!\n";
	system("pause");
	return 2;
}


// FUNCTION DEFINITIONS

int displayMenu()
{
	// Display Main Menu
	system("cls");
	cout << "******* MENU *******\n";
	cout << "\n1. Play";
	cout << "\n2. Database";
	cout << "\n3. Help";
	cout << "\n4. Credits";
	cout << "\n5. Exit";

	// Get User's Choice
	int choice = getNum("\nEnter the choice:\n");
	return choice;
}
