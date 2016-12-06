#include "Database.h"
#include "Input.h"
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;


Database::Database(const string& name)
{
	// make a file to store all data if it not already exists
	ifstream fin(fileName);
	if (!fin) {
		ofstream fout(fileName);
		fout.close();
	}
	else
		fin.close();

	fileName = name;

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
	char ch = 'n';

	do {
		int choice;
		system("cls");
		cout << "\nDATABASE MENU";
		cout << "\n1. Add Player";
		cout << "\n2. Modify Player";
		cout << "\n3. Delete Player";
		cout << "\n4. Display all Players";
		cout << "\n5. Reset all Players";
		cout << "\n6. Delete a team";
		cout << "\n7. Go back to MAIN MENU";
		choice = getNum("Enter your choice:\n");

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
			cout << "\n\nDeleted teams successfully!!";
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

		cout << "\n\n\nDo you want to go to Database Menu(y/n)?\n";
		cin >> ch;

		if (!cin)
			throw runtime_error("End of Input received!!\n");

	} while (ch == 'y' || ch == 'Y');
}


void Database::addPlayer()
{
	system("cls");
	cout << "\t\tADDING PLAYERS";

	string tName = getTeamName("\n\nEnter team of player:\n");

	int posTeam = findPos(teams, Team(tName));

	if (posTeam == -1) {
		char create;
		cout << "\nTeam not found!!";
		cout << "\nDo you want to create a new team named " << tName << " (y/n)?\n";
		cin >> create;

		if (!cin)
			throw runtime_error("End of Input received!!\n");

		if (create == 'y' || create == 'Y') {
			teams.push_back(*(new Team(tName)));
			addPlayer();
		}
	}
	else {
		while (true) {
			cout << "\nEnter the name of player to add:\n";
			string pName;
			getline(cin, pName);

			while (pName == "")
				getline(cin, pName);

			if (!cin)
				throw runtime_error("End of Input received!!\n");

			int posPlayer = findPos(teams[posTeam].players, Player(pName));
			if (posPlayer != -1) {
				cout << "\n\nPlayer already present!!";
			}
			else {
				int pTRuns;
				pTRuns = getPositiveNum("Enter the total runs made by player:\n");
				int pTWickets;
				pTWickets = getPositiveNum("Enter total wickets taken by player:\n");
				int pTMatches;
				pTMatches = getPositiveNum("Enter total matches played by player:\n");
				int pTOvers;
				pTOvers = getPositiveNum("Enter total overs bowled by player:\n");


				teams[posTeam].addPlayer(*(new Player(pName, pTMatches, pTOvers, pTRuns, pTWickets)));

				cout << "\n\nSuccessfully added: " << pName << endl;
				cout << "\nDo you want to add more players(y/n)?\n";
				char choice;

				if (!(choice == 'y' || choice == 'Y'))
					break;
			}
		}
	}



}
void Database::modifyPlayer()
{
	system("cls");
	cout << "\t\tMODIFYING PLAYERS";

	string tName = getTeamName("\n\nEnter team of player:\n");

	int posTeam = findPos(teams, Team(tName));

	if (posTeam == -1) {
		cout << "\nTeam not found!!";
	}
	else {
		system("cls");
		displayTeam(teams[posTeam]);
		string pName;
		cout << "\n\nEnter the player name:\n";
		getline(cin, pName);

		while (pName == "")
			getline(cin, pName);

		if (!cin)
			throw runtime_error("End of Input received!!\n");


		int posPlayer = findPos(teams[posTeam].players, Player(pName));

		if (posPlayer == -1) {
			cout << "\nPlayer not found!!";
		}
		else {
			cout << "\nEnter new details:\n";
			int pTRuns;
			pTRuns = getPositiveNum("Enter the total runs made by player:\n");
			int pTWickets;
			pTWickets = getPositiveNum("Enter total wickets taken by player:\n");
			int pTMatches;
			pTMatches = getPositiveNum("Enter total matches played by player:\n");
			int pTOvers;
			pTOvers = getPositiveNum("Enter total overs bowled by player:\n");

			teams[posTeam].players[posPlayer] = Player(pName, pTMatches, pTOvers, pTRuns, pTWickets);
		}
	}


}

void Database::deletePlayer()
{
	system("cls");
	cout << "\t\tDELETING A PLAYER";

	string tName = getTeamName("\n\nEnter team of player:\n");

	int posTeam = findPos(teams, Team(tName));

	if (posTeam == -1) {
		cout << "\nTeam not found!!";
		return;
	}

	system("cls");
	displayTeam(teams[posTeam]);
	string pName;
	cout << "\n\nEnter the player name:\n";
	getline(cin, pName);

	while (pName == "")
		getline(cin, pName);

	if (!cin)
		throw runtime_error("End of Input received!!\n");


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
	cout << "\t\tDELETING A TEAM";

	string tName = getTeamName("\n\nEnter the team name:\n");

	int posTeam = findPos(teams, Team(tName));

	if (posTeam == -1) {
		cout << "\nTeam not found!!";
		return;
	}
	teams.erase(teams.begin() + posTeam);
	cout << "\nSuccessfully deleted Team: " << tName;

}
void Database::display()
{
	system("cls");

	cout << "\t\tALL PLAYERS RECORD\n\n";
	for (Team& t : teams) {
		displayTeam(t);
		cout << endl;
	}
}


void Database::displayTeam(const Team& team)
{
	cout << endl << "TEAM: " << team.name << endl;
	cout << endl << setw(15) << "Player Name" << setw(20) << "Batting Skills" << setw(20) << "Bowling Skills";
	for (const Player& p : team.players) {
		cout << endl << setw(15) << p.name << setw(20) << p.getBattingSkills() << setw(20) << p.getBowlingSkills();
	}
}
string Database::getTeamName(const string& prompt)
{
	cout << "\n\n\tTEAMS\n";
	for (const Team &t : teams) {
		cout << endl << t.name;
	}

	cout << prompt;
	string tName;
	getline(cin, tName);
	while (tName == "")
		getline(cin, tName);

	if (!cin)
		throw runtime_error("End of Input received!!\n");

	return tName;

}


void Database::write()
{
	ofstream fout(fileName, ios::out);
	if (!fout) {
		cout << "File not opened: " << fileName << endl;
		exit(1);
	}

	for (Team& team : teams) {
		team.write(fout);
	}

	fout.close();
}
void Database::read()
{
	ifstream fin(fileName);
	if (!fin) {
		cout << "Unable to open file: " << fileName << endl;
		exit(1);
	}

	while (fin) {
		Team t;
		t.read(fin);
		teams.push_back(t);
	}
	/*
	int i = 0;
	while (fin.read((char*)&teams[i], sizeof(teams[i]))) {
	i++;
	}*/

	fin.close();

}