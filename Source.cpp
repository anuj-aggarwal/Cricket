#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>

#include "Team.h"
#include "Result.h"
#include "Ball.h"
#include "Input.h"
#include "Database.h"
#include "Help.h"

using namespace std;


void init_play();
int displayMenu();


int posPlayingTeam(const string&);
bool Toss(const string&, const string&);
void play();
int innings(Team&, Team&);
int match(Team&, Team&);



const int noOfWickets = 1;
const int noOfBalls = 30;
const int ballsPerOver = 6;

const string fileName = "../Cricket/Details.txt";
const vector<string> helpFileNames = { "../Cricket/Help/Help.txt", "../Cricket/Help/DatabaseHelp.txt", "../Cricket/Help/RulesHelp.txt", "../Cricket/Help/GamePlayHelp.txt" };


int leftWickets;
int leftBalls;


Database database(fileName);
vector<Team>& teams = database.getTeams();

Help help(helpFileNames);

int main()
try {
	char ch;

	do {
		int choice;
		choice = displayMenu();

		switch (choice) {

		case 1:
			database.menu();
			break;

		case 2:
			play();
			break;

		case 3:
			help.displayHelp();
			break;

		case 4:
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







void init_play()
{
	leftWickets = noOfWickets;
	leftBalls = noOfBalls;


	// get random value acc. to current system time
	time_t time1;
	time(&time1);
	srand((unsigned int)time1);

}

int displayMenu()
{
	system("cls");
	int choice;
	cout << "MENU\n";
	cout << "\n1. Database";
	cout << "\n2. Play";
	cout << "\n3. Help";
	cout << "\n4. Exit";
	choice = getNum("\nEnter the choice:\n");
	return choice;
}



int posPlayingTeam(const string& prompt)
{
	int pos = -1;

	while (pos == -1) {

		string teamName= getString(prompt);
		
		pos = findPos(teams, Team(teamName));
		if (pos == -1) {
			cout << "\nTeam not found: " << teamName << "!! Please try again.....\n";
		}
		else if (!teams[pos].canPlay(noOfWickets, ceil(static_cast<double>(noOfBalls) / ballsPerOver))) {
			cout << endl << teams[pos].name << " has only " << teams[pos].players.size() << " players!!";
			int bowlersReq = ceil(static_cast<double>(noOfBalls) / ballsPerOver / 4);
			cout << "\nMinimum players required to play : " << (noOfWickets > bowlersReq ? noOfWickets : bowlersReq) << "\n\n";
			pos = -1;
		}

	}

	return pos;
}

bool toss(const string& name1, const string& name2)
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
	// Find eligible teams
	int eligibleTeams = 0;

	for (Team t : teams) {
		if (t.canPlay(noOfWickets, ceil(static_cast<double>(noOfBalls) / ballsPerOver)))
			++eligibleTeams;
	}

	if (eligibleTeams < 2) {
		cout << "\nNot enough teams to play!!\n\n";
		return;
	}

	system("cls");
	cout << "\t\tPLAY";
	cout << "\n\n\tTEAMS\n";

	for (const Team &t : teams) {
		cout << endl << t.name;
	}


	int pos1 = posPlayingTeam("\n\nEnter name of first team:\n");

	int pos2 = posPlayingTeam("\n\nEnter name of second team:\n");

	while (pos2 == pos1) {
		cout << "\nTeam: " << teams[pos2].name << " already playing!! Please try again.....\n";
		pos2 = posPlayingTeam("\n\nEnter name of second team:\n");
	}


	init_play();

	if (toss(teams[pos1].name, teams[pos2].name)) {
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

	vector<Player> batsmanPlayed;

	Player* batsman = battingTeam.getNextBatsman(batsmanPlayed);
	Player* bowler = bowlingTeam.getNextBowler();

	system("cls");
	cout << "\n\nOver: 1\n";
	while (leftWickets > 0 && leftBalls > 0) {

		if (leftBalls != noOfBalls && leftBalls%ballsPerOver == 0) {
			cout << "\nEnd of Over!!\nRuns till now: " << totalRuns << endl;
			bowler = bowlingTeam.getNextBowler();
			system("cls");
			cout << "\n\nOver: " << (noOfBalls - leftBalls) / ballsPerOver + 1 << endl;
		}

		Result result;
		Ball b(*batsman, *bowler);
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
			(*batsman).increaseRuns(1);
			break;

		case Result::DOUBLE:
			cout << "Double.\n";
			totalRuns += 2;
			(*batsman).increaseRuns(2);
			break;

		case Result::TRIPLE:
			cout << "Triple.\n";
			totalRuns += 3;
			(*batsman).increaseRuns(3);
			break;

		case Result::FOUR:
			cout << "Four.\n";
			totalRuns += 4;
			(*batsman).increaseRuns(4);
			totalFours++;
			break;

		case Result::SIX:
			cout << "Six!!\n";
			totalRuns += 6;
			(*batsman).increaseRuns(6);
			totalSixes++;
			break;

		case Result::OUT:
			cout << "Out!!\n";
			leftWickets--;
			battingTeam.playerOut((*batsman));
			if (leftWickets > 0)
				batsman = battingTeam.getNextBatsman(batsmanPlayed);
			(*bowler).increaseWickets(1);
			break;

		case Result::RUNOUT:
			cout << "Run Out!!\n";
			leftWickets--;
			battingTeam.playerOut((*batsman));
			if (leftWickets > 0)
				batsman = battingTeam.getNextBatsman(batsmanPlayed);
			(*bowler).increaseWickets(1);
			break;

		}


	}

	cout << "\nEND OF INNINGS........!!\n";

	battingTeam.updateBatsmen(batsmanPlayed);
	bowlingTeam.updateBowlers();

	battingTeam.reset();
	bowlingTeam.reset();

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