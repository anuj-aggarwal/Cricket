#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
#include <cstdlib>
#include <chrono>
#include <thread>


#include "Player.h"
#include "Team.h"
#include "Work.h"
#include "Result.h"
#include "Ball.h"

using namespace std;

void wait(string ch);
void wait();
void init();
int displayMenu();
int innings(Team&, Team&);
void match(Team&, Team&);

void write(string, vector<Team>&);
vector<Team> read(string);

const int noOfWickets = 1;
const int noOfBalls = 30;
const int ballsPerOver = 6;
const string fileName = "Details.txt";

int leftWickets;
int leftBalls;

int main()
try {
	init();
	int choice;
	choice = displayMenu();

	switch (choice) {

	case 1:
		break;

	case 2:
	{
		vector<Team> teams;
		teams = read(fileName);
		if (teams.size() < 2) {
			throw runtime_error("Not enough teams to play!!");
		}

		int pos1 = -1;
		cout << "Enter name of first team:\n";
		string firstTeam;
		cin >> firstTeam;

		for (int i = 0; i < teams.size(); ++i) {
			if (firstTeam == teams[i].name) {
				pos1 = i;
				break;
			}
		}
		if (pos1 == -1) {
			throw runtime_error( "Team not found: " + firstTeam);
		}



		int pos2 = -1;
		cout << "Enter name of second team:\n";
		string secondTeam;
		cin >> secondTeam;

		for (int i = 0; i < teams.size(); ++i) {
			if (secondTeam == teams[i].name) {
				pos2 = i;
				break;
			}
		}
		if (pos2 == -1) {
			throw runtime_error("Team not found: " + secondTeam);
		}


		match(teams[pos1], teams[pos2]);
		write(fileName, teams);

		break;
	}

	case 3:
		cout << "\nEND OF PROGRAM\n";
		wait();
		exit(0);

	default:
		cout << "Wrong choice!!\n";
		wait();
		exit(1);
	}


	//Team t("FIRST", vector<Player>{ Player("a", 5,5, 0, 0), Player("b", 5,5, 100, 3) }, Work::BAT);
	//Team t1("SECOND", { Player("c",5, 5, 0, 0), Player("d", 5, 5,100, 3) }, Work::BOWL);

	//vector<Team> teams = { t, t1 };
	//write("Details.dat", teams);

	//vector<Team> readTeams;
	//read("Details.dat", readTeams);
	//cout << innings(readTeams[0], readTeams[1]);

	///*cout << innings(t, t1);*/

	wait();
	return 0;
}
catch (exception& e) {
	cerr << e.what() << endl;
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
	cout << "\nPress "<<ch<<" to continue: ";
	string c;
	cin >> c;
	while (c != ch) {
		cout << "\nPress "<<ch<<" to continue: ";
		cin >> c;
	}
}
void wait()
{

	cout << "\nPress any key to continue: ";
	string ch;
	cin >> ch;

}
void init()
{
	leftWickets = noOfWickets;
	leftBalls = noOfBalls;


	// get random value acc. to current system time
	time_t time1;
	time(&time1);
	srand((unsigned int)time1);

	// make a file to store all data if it not already exists
	ifstream fin(fileName);
	if (!fin) {
		ofstream fout(fileName);
	}

}
int displayMenu()
{
	int choice;
	cout << "\n\nMENU\n";
	cout << "\n1. Database";
	cout << "\n2. Play";
	cout << "\n3. Exit";
	cout << "\nEnter the choice:\n";
	cin >> choice;
	return choice;
}
int innings(Team& battingTeam, Team& bowlingTeam)
{
	init();

	int totalRuns = 0;
	int totalFours = 0;
	int totalSixes = 0;
	int totalWickets = 0;

	unordered_map<Player, int> oversBowled;
	vector<Player> batsmanPlayed;

	Player batsman = battingTeam.getNextBatsman(batsmanPlayed);
	Player bowler = bowlingTeam.getNextBowler(oversBowled);

	while (leftWickets > 0 && leftBalls > 0) {

		if (leftBalls != noOfBalls && leftBalls%ballsPerOver == 0) {
			cout << "\nEnd of Over!!\nRuns till now: " << totalRuns << endl;
			bowler = bowlingTeam.getNextBowler(oversBowled);
		}

		Result result;
		Ball b(batsman, bowler);
		result = b.getResult();
		leftBalls--;


		cout << "\nBowl " << noOfBalls - leftBalls << ": ";
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
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
void match(Team& t1, Team& t2)
{
	system("cls");
	cout << "\n\nINNINGS 1:\n";
	int runst1 = innings(t1, t2);
	cout << "\nRuns made by first team: " << runst1;

	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	system("cls");
	cout << "\n\nINNINGS 2:\n";
	int runst2 = innings(t2, t1);
	cout << "\nRuns made by second team: " << runst2;

	std::this_thread::sleep_for(std::chrono::milliseconds(2000));

	system("cls");
	if (runst1 > runst2) {
		cout << "\n" << t1.name << " Wins by " << runst1 - runst2 << " runs!!\n";
	}
	else if (runst1 < runst2) {
		cout << "\n" << t2.name << " Wins by " << runst2 - runst1 << " runs!!\n";
	}
	else {
		cout << "\nDRAW between " << t1.name << " and " << t2.name;
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