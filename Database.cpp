#include "Database.h"
#include "Input.h"
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;


Database::Database(const string& fileName)
	:fileName{fileName}
{
	// make a file to store all data if it not already exists
	ifstream inFile(fileName);
	if (!inFile) {
		ofstream outFile(fileName);
		outFile.close();
	}
	else
		inFile.close();

	read();
}
Database::~Database()
{
	write();
}


vector<Team>& Database::getTeams()
{
	// TODO: insert return statement here
	return teams;
}


void Database::menu()
{
	char input = 'n';

	do {
		int choice;
		system("cls");
		cout << "***** DATABASE MENU *****\n";
		cout << "\n1. Add Player";
		cout << "\n2. Modify Player";
		cout << "\n3. Delete Player";
		cout << "\n4. Display all Players";
		cout << "\n5. Reset all Players";
		cout << "\n6. Delete a team";
		cout << "\n7. Go back to MAIN MENU";
		choice = getNum("\nEnter your choice:\n");

		switch (choice) {
		case 1:
			addPlayer();
			break;

		case 2:
			modifyPlayer();
			break;

		case 3:
			deletePlayer();
			break;

		case 4:
			display();
			break;

		case 5:
			teams.clear();
			cout << "\n\nDeleted all teams successfully!!";
			break;

		case 6:
			deleteTeam();
			break;

		case 7:
			return;

		default:
			cout << "\nWrong choice!!";
			break;
		}

		_sleep(2000);
		system("cls");
		input = getChar("Do you want to go to Database Menu(y/n)?\n");

	} while (input == 'y' || input == 'Y');
}


void Database::addPlayer()
{
	system("cls");
	cout << "******** ADDING PLAYERS ********";

	string tName = getTeamName("\n\nEnter team of player:\n");

	int posTeam = findPos(teams, Team(tName));

	if (posTeam == -1) {
		cout << "\nTeam not found!!";

		char create = getChar("\nDo you want to create a new team named " + tName + " (y/n)?\n");

		if (create == 'y' || create == 'Y') {
			teams.push_back(Team(tName));
			cout << "\n\nSuccessfully added new Team: " << tName;
			_sleep(2000);
			addPlayer();
		}
	}
	else {
		while (true) {
			system("cls");
			string pName = getString("Enter the name of player to add:\n");

			int posPlayer = findPos(teams[posTeam].players, Player(pName));
			if (posPlayer != -1) {
				cout << "\n\nPlayer already present!!";
			}
			else {

				teams[posTeam].addPlayer(getPlayer(pName, ""));

				cout << "\n\nSuccessfully added: " << pName << endl;

				char choice = getChar("\nDo you want to add more players(y/n)?\n");

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

	string tName = getTeamName("\n\nEnter team of player:\n");

	int posTeam = findPos(teams, Team(tName));

	if (posTeam == -1) {
		cout << "\nTeam not found!!";
	}
	else {
		system("cls");
		displayTeam(teams[posTeam]);
		string pName = getString("\n\nEnter the player name:\n");

		int posPlayer = findPos(teams[posTeam].players, Player(pName));

		if (posPlayer == -1) {
			cout << "\nPlayer not found!!";
		}
		else {

			teams[posTeam].players[posPlayer] = getPlayer(pName, "\nEnter new details:\n");
			cout << "\n\nSuccessfully modified Player: " << pName;
		}
	}


}

void Database::deletePlayer()
{
	system("cls");
	cout << "******** DELETING A PLAYER ********";

	string tName = getTeamName("\n\nEnter team of player:\n");

	int posTeam = findPos(teams, Team(tName));

	if (posTeam == -1) {
		cout << "\nTeam not found!!";
		return;
	}

	system("cls");
	displayTeam(teams[posTeam]);
	string pName = getString("\n\nEnter the player name:\n");

	int posPlayer = findPos(teams[posTeam].players, Player(pName));
	if (posPlayer == -1) {
		cout << "\nPlayer not found!!";
		return;
	}

	teams[posTeam].players.erase(teams[posTeam].players.begin() + posPlayer);
	cout << "\nSuccessfully deleted Player: " << pName;


}
void Database::deleteTeam()
{
	system("cls");
	cout << "******** DELETING A TEAM ********";

	string tName = getTeamName("\n\nEnter the team name:\n");

	int posTeam = findPos(teams, Team(tName));

	if (posTeam == -1) {
		cout << "\nTeam not found!!";
		return;
	}
	teams.erase(teams.begin() + posTeam);
	cout << "\nSuccessfully deleted Team: " << tName;

}
void Database::display() const
{
	system("cls");

	cout << "*****************  ALL PLAYERS RECORD  *****************\n\n";
	for (const Team& team : teams) {
		displayTeam(team);
		cout << "\n\n\n\n";
	}
	system("pause");
}


void Database::displayTeam(const Team& team) const
{
	int nStars = (42 - team.name.length()) / 2;
	for (int i = 0; i < nStars; ++i)
		cout << "*";

	cout << "  TEAM:    " << team.name << "  ";

	for (int i = 0; i < nStars; ++i)
		cout << "*";

	cout << "\n\n" << setw(15) << "Player Name" << setw(20) << "Batting Skills" << setw(20) << "Bowling Skills";
	for (const Player& p : team.players) {
		cout << endl << setw(15) << p.name << setw(20) << p.getBattingSkills() << setw(20) << p.getBowlingSkills();
	}

	cout << "\n#-----------------------------------------------------#";
}
string Database::getTeamName(const string& prompt) const
{
	cout << "\n\n*******************\n#      TEAMS      #\n*******************\n";
	for (const Team &team : teams) {
		cout << endl << team.name;
	}
	cout << "\n\n#-----------------#";

	string tName = getString(prompt);

	return tName;

}
Player Database::getPlayer(const string& pName, const string& prompt) const
{
	cout << prompt;

	int pTRuns;
	pTRuns = getPositiveNum("Enter the total runs made by player:\n");
	int pTWickets;
	pTWickets = getPositiveNum("Enter total wickets taken by player:\n");
	int pTMatches;
	pTMatches = getPositiveNum("Enter total matches played by player:\n");
	int pTOvers;
	pTOvers = getPositiveNum("Enter total overs bowled by player:\n");

	return Player(pName, pTMatches, pTOvers, pTRuns, pTWickets);
}


void Database::write() const
{
	ofstream outFile(fileName);
	if (!outFile) {
		throw runtime_error("File not opened: " + fileName +"\n");
	}

	for (const Team& team : teams) {
		team.write(outFile);
	}

	outFile.close();
}
void Database::read()
{
	ifstream inFile(fileName);
	if (!inFile) {
		throw runtime_error("Unable to open file: " + fileName + "\n");
	}

	while (inFile) {
		Team team;
		team.read(inFile);
		teams.push_back(team);
	}
	/*
	int i = 0;
	while (inFile.read((char*)&teams[i], sizeof(teams[i]))) {
	i++;
	}*/

	inFile.close();

}