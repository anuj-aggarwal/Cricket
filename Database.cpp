#include "Database.h"

#include <iostream>	// For cout
#include <iomanip>	// For setw()
#include <fstream>	// For ifstream, ofstream

#include "Input.h"	// For getNum(), getPositiveNum(), getString(), getChar()


using namespace std;


Database::Database(const string& fileName)	// Constructor to initialize fileName, check for its existence and call read()
	:fileName{fileName}
{
	// Check for the existence of the file
	ifstream inFile(fileName);
	if (!inFile) {
		// Create a file with that name if it not already exists
		ofstream outFile(fileName);
		outFile.close();
	}
	else
		inFile.close();

	read();
}

Database::~Database()	// Destructor to write all the data to the file at the end of scope of Database
{
	write();	// Writes all the data to the file, fileName
}


// PUBLIC MEMBER FUNCTIONS
vector<Team>& Database::getTeams()	// Accessor
									// Returns a reference to its own teams
{
	return teams;
}

void Database::menu()
{
	char input = 'n';

	do {	// Loop untill the User's asks to go back to Main Menu

		// Display the Menu
		int choice;
		system("cls");
		cout << "***** DATABASE MENU *****\n";
		cout << "\n1. Display all Players";
		cout << "\n2. Add Player";
		cout << "\n3. Modify Player";
		cout << "\n4. Delete Player";
		cout << "\n5. Delete a team";
		cout << "\n6. Reset all Players";
		cout << "\n7. Go back to MAIN MENU";
		choice = getNum("\nEnter your choice:\n");

		// Call different functions apropriately
		switch (choice) {
		case 1:
			// Display all Players
			display();
			break;

		case 2:
			// Add Player
			addPlayer();
			break;

		case 3:
			// Modify Player
			modifyPlayer();
			break;

		case 4:
			// Delete a player
			deletePlayer();
			break;

		case 5:
			// Delete a team
			deleteTeam();
			break;

		case 6:
			// Delete all Players
			teams.clear();
			cout << "\n\nDeleted all teams successfully!!";
			break;

		case 7:
			// Go back to Main Menu
			// Leave the Database Menu
			return;

		default:	// Loop again if User enters wrong Choice
			cout << "\nWrong choice!!";
			break;
		}

		// Ask if User wants to go back to the Database Menu
		_sleep(2000);
		system("cls");
		input = getChar("Do you want to go to Database Menu(y/n)?\n");

		// Anything else except y/Y means NO
	} while (input == 'y' || input == 'Y');
}


// PRIVATE MEMBER FUNCTIONS

void Database::display() const	// Display all the details of the Players and Teams
{
	system("cls");

	cout << "*****************  ALL PLAYERS RECORD  *****************\n\n";
	for (const Team& team : teams) {	// For each Team in teams
		displayTeam(team);	// Display the Players of the Team
		cout << "\n\n\n\n";
	}
	system("pause");
}

void Database::addPlayer()
{
	system("cls");
	cout << "******** ADDING PLAYERS ********";

	// Get Team Name
	string tName = getTeamName("\n\nEnter team of player:\n");

	int posTeam = findPos(teams, Team(tName));	// returns -1 if not found

	if (posTeam == -1) {	// Invalid Team
		cout << "\nTeam not found!!";

		// Ask to create a new Team
		char create = getChar("\nDo you want to create a new team named " + tName + " (y/n)?\n");

		if (create == 'y' || create == 'Y') {	// Cretae a new Team
			teams.push_back(Team(tName));
			cout << "\n\nSuccessfully added new Team: " << tName;
			_sleep(2000);
			addPlayer();	// Call adPlayer() again to add Player to new Team
		}
	}

	else {
		// We got a valid Team
		while (true) {	// Loop till User wants to add more Players
			system("cls");
			string pName = getString("Enter the name of player to add:\n");

			// Check if the Player already exists in Team
			int posPlayer = findPos(teams[posTeam].players, Player(pName));
			if (posPlayer != -1) {
				cout << "\n\nPlayer already present!!";
			}
			else {
				// Player is not present already
				teams[posTeam].addPlayer(getPlayer(pName, ""));	// Add player to the team
												// getPlayer() gets details from User and returns a Player
				cout << "\n\nSuccessfully added: " << pName << endl;

				char choice = getChar("\nDo you want to add more players(y/n)?\n");

				// Anything except y/Y is NO
				if (!(choice == 'y' || choice == 'Y'))
					break;
			}
		}
	}



}

void Database::modifyPlayer()
{
	system("cls");
	cout << "******** MODIFYING PLAYERS ********";

	string tName = getTeamName("\n\nEnter team of player:\n");	// Get team of the Player

	int posTeam = findPos(teams, Team(tName));	// returns -1 if Team is not present

	if (posTeam == -1) {
		cout << "\nTeam not found!!";
	}
	else {
		// We got a valid Team
		system("cls");
		displayTeam(teams[posTeam]);	// Display the Players of the Team

		string pName = getString("\n\nEnter the player name:\n");

		int posPlayer = findPos(teams[posTeam].players, Player(pName));	// returns -1 if Player not present

		if (posPlayer == -1) {
			cout << "\nPlayer not found!!";
		}
		else {
			// We got a valid Player of a valid Team
			teams[posTeam].players[posPlayer] = getPlayer(pName, "\nEnter new details:\n");
														// Gets details from User and returns a Player
			cout << "\n\nSuccessfully modified Player: " << pName;
		}
	}

}

void Database::deletePlayer()
{
	system("cls");
	cout << "******** DELETING A PLAYER ********";

	string tName = getTeamName("\n\nEnter team of player:\n");	// Get name of Team of a Player

	int posTeam = findPos(teams, Team(tName));	// returns -1 if Team not found

	if (posTeam == -1) {
		cout << "\nTeam not found!!";
		return;
	}

	// We got a valid team
	system("cls");
	displayTeam(teams[posTeam]);	// Display the Players of the Team

	string pName = getString("\n\nEnter the player name:\n");	// Ask for the name of Player to delete

	int posPlayer = findPos(teams[posTeam].players, Player(pName));	// returns -1 if Player not found in the Team

	if (posPlayer == -1) {
		cout << "\nPlayer not found!!";
		return;
	}

	// We got a valid player in a valid Team
	teams[posTeam].players.erase(teams[posTeam].players.begin() + posPlayer);	// Delete the Player
	cout << "\nSuccessfully deleted Player: " << pName;


}

void Database::deleteTeam()
{
	system("cls");
	cout << "******** DELETING A TEAM ********";

	string tName = getTeamName("\n\nEnter the team name:\n");	// Get the name of Team to delete

	int posTeam = findPos(teams, Team(tName));	// returns -1 if Team is not present

	if (posTeam == -1) {
		cout << "\nTeam not found!!";
		return;
	}

	// We got a valid Team
	teams.erase(teams.begin() + posTeam);	// Delete the Team
	cout << "\nSuccessfully deleted Team: " << tName;

}


void Database::displayTeam(const Team& team) const
{
	int nStars = (42 - team.name.length()) / 2;	// Decide number of Stars in begnning and End
	for (int i = 0; i < nStars; ++i)	// Display the Starting Stars
		cout << "*";

	// Display the team name
	cout << "  TEAM:    " << team.name << "  ";

	for (int i = 0; i < nStars; ++i)	// Display the Trailing Stars
		cout << "*";

	// Display the Players of the Team
	cout << "\n\n" << setw(15) << "Player Name" << setw(20) << "Batting Skills" << setw(20) << "Bowling Skills";
	for (const Player& p : team.players) {
		cout << endl << setw(15) << p.name << setw(20) << p.getBattingSkills() << setw(20) << p.getBowlingSkills();
	}

	cout << "\n#-----------------------------------------------------#";
}
string Database::getTeamName(const string& prompt) const
{
	cout << "\n\n*******************\n#      TEAMS      #\n*******************\n";

	for (const Team &team : teams) {	// For each Team in teams
		cout << endl << team.name;	// Display the team name
	}
	cout << "\n\n#-----------------#";

	// get the team name
	string tName = getString(prompt);
	return tName;

}
Player Database::getPlayer(const string& pName, const string& prompt) const
{
	cout << prompt;

	// Get Player Data
	int pTRuns;
	pTRuns = getPositiveNum("Enter the total runs made by player:\n");
	int pTWickets;
	pTWickets = getPositiveNum("Enter total wickets taken by player:\n");
	int pTMatches;
	pTMatches = getPositiveNum("Enter total matches played by player:\n");
	int pTOvers;
	pTOvers = getPositiveNum("Enter total overs bowled by player:\n");

	// Return a new Player(copy)
	return Player(pName, pTMatches, pTOvers, pTRuns, pTWickets);
}


void Database::write() const
{
	ofstream outFile(fileName);
	if (!outFile) {
		throw runtime_error("File not opened: " + fileName +"\n");
	}

	for (const Team& team : teams) {	// For each team
		team.write(outFile);	// Write the Team in the file
	}

	outFile.close();
}
void Database::read()
{
	ifstream inFile(fileName);
	if (!inFile) {
		throw runtime_error("Unable to open file: " + fileName + "\n");
	}

	while (inFile) {	// while inFile is in good state, i.e. not encountered End of File

		Team team;
		team.read(inFile);	// Read next team
		teams.push_back(team);	// Add the read team to teams
	}

	inFile.close();

}