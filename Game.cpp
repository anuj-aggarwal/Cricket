#include "Game.h"
#include <ctime>
#include <random>
#include <iostream>
#include "Input.h"
#include "Result.h"	// NOT REQUIRED
#include "Ball.h"

using namespace std;

Game::Game(vector<Team>& teams)
	:teams{ teams }, leftWickets{ 0 }, leftBalls{ 0 }
{
}


Game::~Game()
{
}


void Game::init()
{
	leftWickets = nWickets;
	leftBalls = nBalls;


	// get random value acc. to current system time
	time_t currTime;
	time(&currTime);
	srand((unsigned int)currTime);
}


bool Game::tossChoice(const string& tName)
{
	cout << endl << tName << " Won the Toss!!\n\n";

	_sleep(2000);

	int input = getNum(tName + ": You want Batting or Bowling(1/2)?\n");
	while (input != 1 && input != 2) {
		cout << "\nSorry, wrong input!! Please try again.....\n";
		input = getNum(tName + ": You want Batting or Bowling(1/2)?\n");
	}

	if (input == 1) {
		cout << "\n\n" << tName << " won the toss and chose to BAT first.....";
		_sleep(2000);
		cout << "\n\n\nStarting the game.....";
		_sleep(2000);
		return true;
	}
	else {
		cout << "\n\n" << tName << " won the toss and chose to BOWL first.....";
		_sleep(2000);
		cout << "\n\n\nStarting the game.....";
		_sleep(2000);
		return false;
	}
}

bool Game::toss(const string& tName1, const string& tName2)
{
	system("cls");
	cout << "**********  TOSS  **********";
	_sleep(2000);


	int outcome = rand() % 2;
	if (outcome == 0) {
		cout << "\n\nHEADS!!\n";
		_sleep(1000);
		bool choice = tossChoice(tName1);
		if (choice)
			return true;
		return false;
	}
	else {
		cout << "\n\nTAILS!!\n";
		_sleep(1000);
		bool choice = tossChoice(tName2);
		if (choice)
			return false;
		return true;
	}
}


int Game::innings(Team& battingTeam, Team& bowlingTeam)
{
	init();

	int totalRuns = 0;
	int totalFours = 0;
	int totalSixes = 0;
	int totalWickets = 0;

	vector<Player> batsmanPlayed;

	Player* batsman = battingTeam.getNextBatsman(batsmanPlayed);
	Player* bowler = bowlingTeam.getNextBowler();

	system("cls");
	cout << "**********  Over: 1  **********\n";
	while (leftWickets > 0 && leftBalls > 0) {

		if (leftBalls != nBalls && leftBalls%ballsPerOver == 0) {
			_sleep(1000);
			cout << "\nEnd of Over!!\nRuns till now: " << totalRuns << endl;
			_sleep(2000);
			bowler = bowlingTeam.getNextBowler();
			system("cls");
			cout << "**********  Over: " << (nBalls - leftBalls) / ballsPerOver + 1 << "  **********\n";
		}

		Result result;
		Ball b(*batsman, *bowler);
		result = b.getResult();
		leftBalls--;


		cout << "\nBowl " << nBalls - leftBalls << ": ";
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


	battingTeam.updateBatsmen(batsmanPlayed);
	bowlingTeam.updateBowlers();

	battingTeam.reset();
	bowlingTeam.reset();

	return totalRuns;
}


int Game::match(Team& team1, Team& team2)
{
	system("cls");
	cout << "***************  INNINGS 1:  ***************\n";
	int runst1 = innings(team1, team2);
	_sleep(1000);
	cout << "\n#----------- END OF INNINGS 1 -----------#\n";
	_sleep(1000);
	cout << "\nRuns made by first team: " << runst1;

	_sleep(3000);

	system("cls");
	cout << "***************  INNINGS 2:  ***************\n";
	int runst2 = innings(team2, team1);
	_sleep(1000);
	cout << "\n#----------- END OF INNINGS 2 -----------#\n";
	_sleep(1000);
	cout << "\nRuns made by second team: " << runst2;

	_sleep(3000);

	system("cls");

	cout << "************  RESULT  ************\n";
	_sleep(2000);
	if (runst1 > runst2) {
		cout << "\n" << team1.name << " Wins by " << runst1 - runst2 << " runs!!\n";
		return 1;
	}
	else if (runst1 < runst2) {
		cout << "\n" << team2.name << " Wins by " << runst2 - runst1 << " runs!!\n";
		return -1;
	}
	else {
		cout << "\nDRAW between " << team1.name << " and " << team2.name;
		return 0;
	}
	cout << "\n\n";
	_sleep(2000);
}


void Game::play()
{
	// Find eligible teams
	if (!areTeamsEligible())
		return;

	system("cls");
	cout << "***************  PLAY  ***************";
	cout << "\n\n*******************\n#      TEAMS      #\n*******************\n";
	for (const Team &team : teams) {
		cout << endl << team.name;
	}
	cout << "\n\n#-----------------#\n\n";



	int posTeam1 = posPlayingTeam("\n\nEnter name of first team:\n");

	int posTeam2 = posPlayingTeam("\n\nEnter name of second team:\n");

	while (posTeam2 == posTeam1) {
		cout << "\nTeam: " << teams[posTeam2].name << " already playing!! Please try again.....\n";
		posTeam2 = posPlayingTeam("\n\nEnter name of second team:\n");
	}


	init();

	if (toss(teams[posTeam1].name, teams[posTeam2].name)) {
		match(teams[posTeam1], teams[posTeam2]);
	}
	else
		match(teams[posTeam2], teams[posTeam1]);
}


bool Game::areTeamsEligible()
{
	int eligibleTeams = 0;

	for (const Team& team : teams) {
		if (team.canPlay(nWickets, ceil(static_cast<double>(nBalls) / ballsPerOver)))
			++eligibleTeams;
	}

	if (eligibleTeams < 2) {
		cout << "\nNot enough teams to play!!\n\n";
		return false;
	}

	return true;
}


int Game::posPlayingTeam(const string& prompt)
{
	int posTeam = -1;

	while (posTeam == -1) {

		string teamName = getString(prompt);

		posTeam = findPos(teams, Team(teamName));
		if (posTeam == -1) {
			cout << "\nTeam not found: " << teamName << "!! Please try again.....\n";
		}
		else if (!teams[posTeam].canPlay(nWickets, ceil(static_cast<double>(nBalls) / ballsPerOver))) {
			cout << endl << teams[posTeam].name << " has only " << teams[posTeam].players.size() << " players!!";
			int bowlersReq = ceil(static_cast<double>(nBalls) / ballsPerOver / 4);
			cout << "\nMinimum players required to play : " << (nWickets > bowlersReq ? nWickets : bowlersReq) << "\n\n";
			posTeam = -1;
		}

	}

	return posTeam;
}
