#include "Database.h"
#include "Input.h"
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;


Database::Database(string name)
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
	cout << "\n\n\tTEAMS\n";
	for (const Team &t : teams) {
		cout << endl << t.name;
	}

	cout << "\n\nEnter team of player:\n";
	string tname;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, tname);

	if (!cin)
		throw runtime_error("End of Input received!!\n");

	bool found = false;

	for (Team& t : teams)
		if (t.name == tname) {

			cout << "\nEnter the name of player to add:\n";
			string pName;
			getline(cin, pName);

			if (!cin)
				throw runtime_error("End of Input received!!\n");

			for (const Player& p : t.players)
				if (p.name == pName) {
					cout << "\n\nPlayer already present!!";
					return;
				}

			int pTRuns;
			pTRuns = getPositiveNum("Enter the total runs made by player:\n");
			int pTWickets;
			pTWickets = getPositiveNum("Enter total wickets taken by player:\n");
			int pTMatches;
			pTMatches = getPositiveNum("Enter total matches played by player:\n");
			int pTOvers;
			pTOvers = getPositiveNum("Enter total overs bowled by player:\n");


			t.addPlayer(*(new Player(pName, pTMatches, pTOvers, pTRuns, pTWickets)));
			found = true;
			break;
		}

	if (!found) {
		char create;
		cout << "\nTeam not found!!";
		cout << "\nDo you want to create a new team named " << tname << " (y/n)?\n";
		cin >> create;

		if (!cin)
			throw runtime_error("End of Input received!!\n");

		if (create == 'y' || create == 'Y') {
			teams.push_back(*(new Team(tname)));
			addPlayer();
		}
	}

}
void Database::modifyPlayer()
{
	system("cls");
	string tName;
	cout << "\t\tMODIFYING PLAYERS";
	cout << "\n\n\tTEAMS\n";
	for (const Team& t : teams)
		cout << endl << t.name;

	cout << "\n\nEnter the team of player:\n";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, tName);

	if (!cin)
		throw runtime_error("End of Input received!!\n");

	bool teamFound = false;
	for (Team& team : teams) {
		if (team.name == tName) {
			system("cls");
			displayTeam(team);
			string pName;
			cout << "\n\nEnter the player name:\n";
			getline(cin, pName);

			if (!cin)
				throw runtime_error("End of Input received!!\n");

			bool pFound = false;
			for (Player& p : team.players) {
				if (p.name == pName) {

					cout << "\nEnter new details:\n";
					int pTRuns;
					pTRuns = getPositiveNum("Enter the total runs made by player:\n");
					int pTWickets;
					pTWickets = getPositiveNum("Enter total wickets taken by player:\n");
					int pTMatches;
					pTMatches = getPositiveNum("Enter total matches played by player:\n");
					int pTOvers;
					pTOvers = getPositiveNum("Enter total overs bowled by player:\n");

					p = Player(p.name, pTMatches, pTOvers, pTRuns, pTWickets);


					pFound = true;
					break;
				}
			}

			if (!pFound) {
				cout << "\nPlayer not found!!";
			}

			teamFound = true;
			break;
		}
	}

	if (!teamFound) {
		cout << "\nTeam not found!!";
	}

}
void Database::deletePlayer()
{
	string tName;
	system("cls");
	cout << "\t\tDELETING A PLAYER";
	cout << "\n\n\tTEAMS\n";
	for (const Team& t : teams)
		cout << endl << t.name;

	cout << "\n\nEnter the team of player:\n";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, tName);

	if (!cin)
		throw runtime_error("End of Input received!!\n");

	bool teamFound = false;
	for (Team& team : teams) {
		if (team.name == tName) {
			system("cls");
			displayTeam(team);
			string pName;
			cout << "\n\nEnter the player name:\n";
			getline(cin, pName);

			if (!cin)
				throw runtime_error("End of Input received!!\n");

			bool pFound = false;
			for (Player& p : team.players) {
				if (p.name == pName) {

					team.players.erase(find(team.players.begin(), team.players.end(), p));
					cout << "\nSuccessfully deleted Player: " << pName;
					pFound = true;
					break;
				}
			}

			if (!pFound) {
				cout << "\nPlayer not found!!";
			}

			teamFound = true;
			break;
		}
	}

	if (!teamFound) {
		cout << "\nTeam not found!!";
	}

}
void Database::deleteTeam()
{
	string tName;
	system("cls");
	cout << "\t\tDELETING A TEAM";
	cout << "\n\n\tTEAMS\n";
	for (const Team& t : teams)
		cout << endl << t.name;

	cout << "\n\nEnter the team name:\n";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, tName);

	if (!cin)
		throw runtime_error("End of Input received!!\n");

	bool teamFound = false;
	for (Team& team : teams) {
		if (team.name == tName) {
			teams.erase(find(teams.begin(), teams.end(), team));
			cout << "\nSuccessfully deleted Team: " << tName;
			teamFound = true;
			break;
		}
	}

	if (!teamFound) {
		cout << "\nTeam not found!!";
	}

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


void Database::displayTeam(Team& team)
{
	cout << endl << "TEAM: " << team.name << endl;
	cout << endl << setw(15) << "Player Name" << setw(20) << "Batting Skills" << setw(20) << "Bowling Skills";
	for (const Player& p : team.players) {
		cout << endl << setw(15) << p.name << setw(20) << p.getBattingSkills() << setw(20) << p.getBowlingSkills();
	}
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