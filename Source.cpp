#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>

#include "Team.h"
#include "Result.h"
#include "Ball.h"

using namespace std;

void wait(string ch);
void wait();
int getNum(string);
int getPositiveNum(string);

void init_teams();
void init_play();
int displayMenu();
void database();

bool Toss(string&, string&);
void play();
int innings(Team&, Team&);
int match(Team&, Team&);

void write(string, vector<Team>&);
vector<Team> read(string);

const int noOfWickets = 1;
const int noOfBalls = 30;
const int ballsPerOver = 6;
const string fileName = "../Cricket/Details.txt";

int leftWickets;
int leftBalls;
vector<Team> teams;

int main()
try {
	init_teams();
	char ch;

	do {
		int choice;
		choice = displayMenu();

		switch (choice) {

		case 1:
			database();
			break;

		case 2:
			play();
			break;

		case 3:
			write(fileName, teams);
			cout << "\nEND OF PROGRAM\n";
			return 0;

		default:
			cout << "Wrong choice!!\n";
			break;
		}

		cout << "\nDo you want to go to MAIN MENU(y/n)?:\n";
		cin >> ch;

		if (!cin)
			throw runtime_error("End of Input received!!\n");

	} while (ch == 'y' || ch == 'Y');


	//Team t("FIRST", vector<Player>{ Player("a", 5,5, 0, 0), Player("b", 5,5, 100, 3) }, Work::BAT);
	//Team t1("SECOND", { Player("c",5, 5, 0, 0), Player("d", 5, 5,100, 3) }, Work::BOWL);

	//vector<Team> teams = { t, t1 };
	//write("Details.dat", teams);

	//vector<Team> readTeams;
	//read("Details.dat", readTeams);
	//cout << innings(readTeams[0], readTeams[1]);

	///*cout << innings(t, t1);*/

	write(fileName, teams);
	wait();
	return 0;
}
catch (exception& e) {
	cerr << endl << e.what() << endl;
	wait("~");
	return 1;
}
catch (...) {
	cerr << "OOps, Unknown error!!\n";
	wait("~~");
	return 2;
}




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
int getNum(string prompt)
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
int getPositiveNum(string prompt)
{
	int n;
	n = getNum(prompt);
	while (n < 0) {
		cout << "\nSorry, positive number expected(>=0)!!Please try again.....\n";
		n = getNum(prompt);
	}
	return n;
}


void init_play()
{
	leftWickets = noOfWickets;
	leftBalls = noOfBalls;


	// get random value acc. to current system time
	time_t time1;
	time(&time1);
	srand((unsigned int)time1);

}
void init_teams()
{
	// make a file to store all data if it not already exists
	ifstream fin(fileName);
	if (!fin) {
		ofstream fout(fileName);
	}

	teams = read(fileName);
}




void displayTeam(Team& team)
{
	cout << endl << "TEAM: " << team.name << endl;
	cout << endl << setw(15) << "Player Name" << setw(20) << "Batting Skills" << setw(20) << "Bowling Skills";
	for (const Player& p : team.players) {
		cout << endl << setw(15) << p.name << setw(20) << p.getBattingSkills() << setw(20) << p.getBowlingSkills();
	}
}
int displayMenu()
{
	system("cls");
	int choice;
	cout << "MENU\n";
	cout << "\n1. Database";
	cout << "\n2. Play";
	cout << "\n3. Exit";
	choice = getNum("\nEnter the choice:\n");
	return choice;
}
void addPlayer()
{
	system("cls");
	cout << "\t\tADDING PLAYERS";
	cout << "\n\n\tTEAMS\n";
	for (const Team &t : teams) {
		cout << endl << t.name;
	}

	cout << "\n\nEnter team of player:\n";
	string tname;
	cin >> tname;

	if (!cin)
		throw runtime_error("End of Input received!!\n");

	bool found = false;

	for (Team& t : teams)
		if (t.name == tname) {

			cout << "\nEnter the name of player to add:\n";
			string pName;
			cin >> pName;

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
void modifyPlayer()
{
	system("cls");
	string tName;
	cout << "\t\tMODIFYING PLAYERS";
	cout << "\n\n\tTEAMS\n";
	for (const Team& t : teams)
		cout << endl << t.name;

	cout << "\n\nEnter the team of player:\n";
	cin >> tName;

	if (!cin)
		throw runtime_error("End of Input received!!\n");

	bool teamFound = false;
	for (Team& team : teams) {
		if (team.name == tName) {
			system("cls");
			displayTeam(team);
			string pName;
			cout << "\n\nEnter the player name:\n";
			cin >> pName;

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
void deletePlayer()
{
	string tName;
	system("cls");
	cout << "\t\tDELETING A PLAYER";
	cout << "\n\n\tTEAMS\n";
	for (const Team& t : teams)
		cout << endl << t.name;

	cout << "\n\nEnter the team of player:\n";
	cin >> tName;

	if (!cin)
		throw runtime_error("End of Input received!!\n");

	bool teamFound = false;
	for (Team& team : teams) {
		if (team.name == tName) {
			system("cls");
			displayTeam(team);
			string pName;
			cout << "\n\nEnter the player name:\n";
			cin >> pName;

			if (!cin)
				throw runtime_error("End of Input received!!\n");

			bool pFound = false;
			for (Player& p : team.players) {
				if (p.name == pName) {

					team.players.erase(find(team.players.begin(), team.players.end(), p));
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
void deleteTeam()
{
	string tName;
	system("cls");
	cout << "\t\tDELETING A TEAM";
	cout << "\n\n\tTEAMS\n";
	for (const Team& t : teams)
		cout << endl << t.name;

	cout << "\n\nEnter the team of player:\n";
	cin >> tName;

	if (!cin)
		throw runtime_error("End of Input received!!\n");

	bool teamFound = false;
	for (Team& team : teams) {
		if (team.name == tName) {
			teams.erase(find(teams.begin(), teams.end(), team));

			teamFound = true;
			break;
		}
	}

	if (!teamFound) {
		cout << "\nTeam not found!!";
	}

}
void display()
{
	system("cls");

	cout << "\t\tALL PLAYERS RECORD\n\n";
	for (Team& t : teams) {
		displayTeam(t);
		cout << endl;
	}
}

void database()
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
		choice= getNum("Enter your choice:\n");

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



bool toss(string name1, string name2)
{
	system("cls");
	cout << "\t\tTOSS";
	_sleep(2000);

	int input;
	int outcome = rand() % 2;
	if (outcome == 0) {
		cout << "\n\nHEADS!!\n";
		cout << name1 << " Won the Toss!!\n\n";

		_sleep(2000);

		input = getNum(name1 + ": You want Batting or Bowling(1/2)?");
		while (input != 1 && input != 2) {
			cout << "\nSorry, wrong input!! Please try again.....\n";
			input = getNum(name1 + ": You want Batting or Bowling(1/2)?");
		}

		if (input == 1) {
			cout << "\n\n" << name1 << " won the toss and chose to BAT first.....";
			cout << "\nStarting the game.....";
			_sleep(2000);
			return true;
		}
		else {
			cout << "\n\n" << name1 << " won the toss and chose to BOWL first.....";
			cout << "\nStarting the game.....";
			_sleep(2000);
			return false;
		}
	}
	else {
		cout << "\n\nTAILS!!\n";
		cout << name2 << " Won the Toss!!\n\n";

		_sleep(2000);

		input = getNum(name2 + ": You want Batting or Bowling(1/2)?");
		while (input != 1 && input != 2) {
			cout << "\nSorry, wrong input!! Please try again.....\n";
			input = getNum(name2 + ": You want Batting or Bowling(1/2)?");
		}

		if (input == 1) {
			cout << "\n\n" << name2 << " won the toss and chose to BAT first.....";
			cout << "\nStarting the game.....";
			_sleep(2000);
			return false;
		}
		else {
			cout << "\n\n" << name2 << " won the toss and chose to BOWL first.....";
			cout << "\nStarting the game.....";
			_sleep(2000);
			return true;
		}
	}
}
void play()
{
	if (teams.size() < 2) {
		throw runtime_error("Not enough teams to play!!");
	}

	system("cls");
	cout << "\t\tPLAY";
	cout << "\n\n\tTEAMS\n";

	for (const Team &t : teams) {
		cout << endl << t.name;
	}


	int pos1 = -1;
	cout << "\n\nEnter name of first team:\n";
	string firstTeam;
	cin >> firstTeam;

	if (!cin)
		throw runtime_error("End of Input received!!\n");

	for (int i = 0; i < teams.size(); ++i) {
		if (firstTeam == teams[i].name) {
			if (!teams[i].canPlay(noOfWickets))
				throw runtime_error(teams[i].name + " has only " + to_string(teams[i].players.size()) + " players!!\nMinimum players required to play : " + to_string(noOfWickets));
			pos1 = i;
			break;
		}
	}
	if (pos1 == -1) {
		throw runtime_error("Team not found: " + firstTeam);
	}



	int pos2 = -1;
	cout << "\nEnter name of second team:\n";
	string secondTeam;
	cin >> secondTeam;

	if (!cin)
		throw runtime_error("End of Input received!!\n");

	for (int i = 0; i < teams.size(); ++i) {
		if (secondTeam == teams[i].name) {
			if (!teams[i].canPlay(noOfWickets))
				throw runtime_error(teams[i].name + " has only " + to_string(teams[i].players.size()) + " players!!\nMinimum players required to play : " + to_string(noOfWickets));
			pos2 = i;
			break;
		}
	}
	if (pos2 == -1) {
		throw runtime_error("Team not found: " + secondTeam);
	}

	init_play();

	if (toss(firstTeam, secondTeam)) {
		match(teams[pos1], teams[pos2]);
	}
	else
		match(teams[pos2], teams[pos1]);
}
int innings(Team& battingTeam, Team& bowlingTeam)
{
	init_play();

	int totalRuns = 0;
	int totalFours = 0;
	int totalSixes = 0;
	int totalWickets = 0;

	unordered_map<Player, int> oversBowled;
	vector<Player> batsmanPlayed;

	Player batsman = battingTeam.getNextBatsman(batsmanPlayed);
	Player bowler = bowlingTeam.getNextBowler(oversBowled);

	system("cls");
	cout << "\n\nOver: 1\n";
	while (leftWickets > 0 && leftBalls > 0) {

		if (leftBalls != noOfBalls && leftBalls%ballsPerOver == 0) {
			cout << "\nEnd of Over!!\nRuns till now: " << totalRuns << endl;
			bowler = bowlingTeam.getNextBowler(oversBowled);
			system("cls");
			cout << "\n\nOver: " << (noOfBalls - leftBalls) / ballsPerOver + 1 << endl;
		}

		Result result;
		Ball b(batsman, bowler);
		result = b.getResult();
		leftBalls--;


		cout << "\nBowl " << noOfBalls - leftBalls << ": ";
		_sleep(2000);
		switch (result) {

		case Result::ZERO:
			cout << "Zero runs.\n";
			break;

		case Result::ONE:
			cout << "Single.\n";
			totalRuns++;
			batsman.increaseRuns(1);
			break;

		case Result::DOUBLE:
			cout << "Double.\n";
			totalRuns += 2;
			batsman.increaseRuns(2);
			break;

		case Result::TRIPLE:
			cout << "Triple.\n";
			totalRuns += 3;
			batsman.increaseRuns(3);
			break;

		case Result::FOUR:
			cout << "Four.\n";
			totalRuns += 4;
			batsman.increaseRuns(4);
			totalFours++;
			break;

		case Result::SIX:
			cout << "Six!!\n";
			totalRuns += 6;
			batsman.increaseRuns(6);
			totalSixes++;
			break;

		case Result::OUT:
			cout << "Out!!\n";
			leftWickets--;
			battingTeam.playerOut(batsman);
			if (leftWickets > 0)
				batsman = battingTeam.getNextBatsman(batsmanPlayed);
			bowler.increaseWickets(1);
			break;

		case Result::RUNOUT:
			cout << "Run Out!!\n";
			leftWickets--;
			battingTeam.playerOut(batsman);
			batsman = battingTeam.getNextBatsman(batsmanPlayed);
			bowler.increaseWickets(1);
			break;

		}


	}

	cout << "\nEND OF INNINGS........!!\n";

	battingTeam.updateBatsmen(batsmanPlayed);
	bowlingTeam.updateBowlers(oversBowled);

	return totalRuns;
}
int match(Team& t1, Team& t2)
{
	system("cls");
	cout << "INNINGS 1:\n";
	int runst1 = innings(t1, t2);
	cout << "\nRuns made by first team: " << runst1;

	_sleep(2000);
	system("cls");
	cout << "INNINGS 2:\n";
	int runst2 = innings(t2, t1);
	cout << "\nRuns made by second team: " << runst2;

	_sleep(2000);

	system("cls");
	if (runst1 > runst2) {
		cout << "\n" << t1.name << " Wins by " << runst1 - runst2 << " runs!!\n";
		return 1;
	}
	else if (runst1 < runst2) {
		cout << "\n" << t2.name << " Wins by " << runst2 - runst1 << " runs!!\n";
		return -1;
	}
	else {
		cout << "\nDRAW between " << t1.name << " and " << t2.name;
		return 0;
	}
}



void write(string fileName, vector<Team>& t)
{
	ofstream fout(fileName, ios::out);
	if (!fout) {
		cout << "File not opened: " << fileName << endl;
		exit(1);
	}

	for (Team& team : t) {
		team.write(fout);
	}

	fout.close();
}
vector<Team> read(string fileName)
{
	ifstream fin(fileName);
	if (!fin) {
		cout << "Unable to open file: " << fileName << endl;
		exit(1);
	}

	vector<Team> teams;
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
	return teams;

}