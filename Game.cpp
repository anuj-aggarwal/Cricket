#include "Game.h"

#include <ctime>	// For time_t, time()
#include <random>	// For rand(), srand()
#include <iostream>	// For cout

#include "Input.h"	// For getNum(), getString
#include "Result.h"	// Just for completion of Documentation, Not required, already included in Ball.h
#include "Ball.h"

using namespace std;


Game::Game(vector<Team>& teams)	// Constructor to initialize own teams with the given teams vector
	:teams{ teams }, leftWickets{ 0 }, leftBalls{ 0 }
{
}
Game::~Game()	// Destructor
{
}


// PUBLIC MEMBER FUNCTIONS
void Game::play()
{
	// Check if Match is possible or not
	if (!areTeamsEligible())
		return;

	// Start the Play if there are eligible Teams
	system("cls");
	cout << "***************  PLAY  ***************";

	// Display all the eligible teams
	cout << "\n\n*******************\n#      TEAMS      #\n*******************\n";

	for (const Team &team : teams) {	// For each team in teams
		// Display the team if it is eligible to play
		if (team.canPlay(nWickets, ceil(static_cast<double>(nBalls) / ballsPerOver)))
			cout << endl << team.name;
	}
	cout << "\n\n#-----------------#\n\n";


	// Get position of first Playing Team
	int posTeam1 = posPlayingTeam("\n\nEnter name of first team:\n");
	// Get position of second Playing Team
	int posTeam2 = posPlayingTeam("\n\nEnter name of second team:\n");

	while (posTeam2 == posTeam1) {	// Ask for second Team untill user enters a valid Team different from first Team
		cout << "\nTeam: " << teams[posTeam2].name << " already playing!! Please try again.....\n";
		// Try to get the Team again
		posTeam2 = posPlayingTeam("\n\nEnter name of second team:\n");
	}
	// We got the two teams to play

	// Initialize the parameters, and seed rand()
	init();

	// TOSS
	if (toss(teams[posTeam1].name, teams[posTeam2].name)) {
		// If toss returned true, i.e. First Team gets the first Batting
		match(teams[posTeam1], teams[posTeam2]);	// match with Team 1 as the first Batting Team
	}
	else	// If Toss returned false, i.e. First Team gets the first Bowling
		match(teams[posTeam2], teams[posTeam1]);	//match with Team 2 as the first Batting Team
}


// PRIVATE MEMBER FUNCTIONS

void Game::match(Team& team1, Team& team2)
{
	// Assumes first Team is the Team to Bat First

	// INNINGS 1
	system("cls");
	cout << "***************  INNINGS 1:  ***************\n";
	int runst1 = innings(team1, team2);	// Simulate the innings and get the Runs Scored
	_sleep(1000);
	cout << "\n#----------- END OF INNINGS 1 -----------#\n";
	_sleep(1000);
	cout << "\nRuns made by first team: " << runst1;
	_sleep(3000);


	// INNINGS 2
	system("cls");
	cout << "***************  INNINGS 2:  ***************\n";
	int runst2 = innings(team2, team1);	// Simulate the innings with team2 as Batting Team now and gets the Runs scored
	_sleep(1000);
	cout << "\n#----------- END OF INNINGS 2 -----------#\n";
	_sleep(1000);
	cout << "\nRuns made by second team: " << runst2;
	_sleep(3000);

	// Display the Final Result
	system("cls");
	cout << "************  RESULT  ************\n";
	_sleep(2000);
	if (runst1 > runst2) {
		cout << "\n" << team1.name << " Wins by " << runst1 - runst2 << " runs!!\n";
	}
	else if (runst1 < runst2) {
		cout << "\n" << team2.name << " Wins by " << runst2 - runst1 << " runs!!\n";
	}
	else {		// runst1 == runst2, i.e. a DRAW
		cout << "\nDRAW between " << team1.name << " and " << team2.name;
	}
	cout << "\n\n";
	_sleep(2000);
}

int Game::innings(Team& battingTeam, Team& bowlingTeam)
{
	init();	// Initialize the Game Parameters

	int totalRuns = 0;

	vector<Player> batsmanPlayed;	// Stores all the batsmen who did Batting in the Innings

	// Get the Opening Batsman and Bowler from the two teams
	Player* batsman = battingTeam.getNextBatsman(batsmanPlayed);
	Player* bowler = bowlingTeam.getNextBowler();

	// Actual Start of Innings
	system("cls");
	cout << "**********  Over: 1  **********\n";
	while (leftWickets > 0 && leftBalls > 0) {

		if (leftBalls != nBalls && leftBalls%ballsPerOver == 0) {
			// Over is ended if left Balls is a multiple of balls per over
			_sleep(1000);
			cout << "\nEnd of Over!!\nRuns till now: " << totalRuns << endl;
			_sleep(2000);
			// Get Bowler to bowl next Over
			bowler = bowlingTeam.getNextBowler();
			system("cls");
			cout << "**********  Over: " << (nBalls - leftBalls) / ballsPerOver + 1 << "  **********\n";	// Start of next Over
		}

		Result result;	// Stores result of next Ball

		Ball b(*batsman, *bowler);
		result = b.getResult();	// Get result of the current Ball
		leftBalls--;


		cout << "\nBowl " << nBalls - leftBalls << ": ";
		_sleep(2000);

		switch (result) {
					// Do the appropriate according to possible values of Result
		case Result::ZERO:
			cout << "Zero runs.\n";
			break;

		case Result::ONE:
			cout << "Single.\n";
			totalRuns++;
			(*batsman).increaseRuns(1);	// Increase total Runs Scored by Batsman
			break;

		case Result::DOUBLE:
			cout << "Double.\n";
			totalRuns += 2;
			(*batsman).increaseRuns(2);	// Increase total Runs Scored by Batsman
			break;

		case Result::TRIPLE:
			cout << "Triple.\n";
			totalRuns += 3;
			(*batsman).increaseRuns(3);	// Increase total Runs Scored by Batsman
			break;

		case Result::FOUR:
			cout << "Four.\n";
			totalRuns += 4;
			(*batsman).increaseRuns(4);	// Increase total Runs Scored by Batsman
			break;

		// No 5 runs for this version of the Game Simulator
		case Result::SIX:
			cout << "Six!!\n";
			totalRuns += 6;
			(*batsman).increaseRuns(6);	// Increase total Runs Scored by Batsman
			break;

		case Result::OUT:
			cout << "Out!!\n";
			battingTeam.playerOut((*batsman));	// Declare the batsman to be out to the Batting Team
			
			leftWickets--;
			if (leftWickets > 0)	// Get next Batsman only if Wickets are left, else, Game Over
				batsman = battingTeam.getNextBatsman(batsmanPlayed);

			(*bowler).increaseWickets(1);	// Increase total Wickets taken by Bowler
			break;

		case Result::RUNOUT:
			cout << "Run Out!!\n";
			battingTeam.playerOut((*batsman));	// Declare the batsman to be out to the Batting Team

			leftWickets--;
			if (leftWickets > 0)	// Get next Batsman only if Wickets are left, else, Game Over
				batsman = battingTeam.getNextBatsman(batsmanPlayed);
			
			(*bowler).increaseWickets(1);	// Increase total Wickets taken by Bowler
			break;

		}


	}

	// Update the Total Matches and total Overs of Batsmen and Bowers who did Batting/ bowled Overs
	battingTeam.updateBatsmen(batsmanPlayed);
	bowlingTeam.updateBowlers();

	// Reset the out Batsmen and the overs Bowled by the Bowlers
	battingTeam.reset();
	bowlingTeam.reset();

	return totalRuns;
}

int Game::posPlayingTeam(const string& prompt)
{
	int posTeam = -1;	// Signal for not got playing team yet

	while (posTeam == -1) {
		// While we do not get a valid Playing Team
		string teamName = getString(prompt);

		posTeam = findPos(teams, Team(teamName));	// Returns -1 if Team is not found
		if (posTeam == -1) {	// User entered Wrong Team name
			cout << "\nTeam not found: " << teamName << "!! Please try again.....\n";
		}
		else if (!teams[posTeam].canPlay(nWickets, ceil(static_cast<double>(nBalls) / ballsPerOver))) {
			// Team entered is not eligible to play
			cout << endl << teams[posTeam].name << " has only " << teams[posTeam].players.size() << " players!!";

			int bowlersReq = ceil(static_cast<double>(nBalls) / ballsPerOver / 4);
			cout << "\nMinimum players required to play : " << (nWickets > bowlersReq ? nWickets : bowlersReq) << "\n\n";
			posTeam = -1;	// We did not get a Playing Team yet
		}

	}

	return posTeam;
}

bool Game::toss(const string& tName1, const string& tName2)
{
	system("cls");
	cout << "**********  TOSS  **********";
	_sleep(2000);

	int outcome = rand() % 2;	// Get 0 or 1 randomly

	if (outcome == 0) {	// HEADS
		cout << "\n\nHEADS!!\n";
		_sleep(1000);
		bool choice = tossChoice(tName1);	// Get the Choice of Team which Won the Toss
		
		if (choice)	// Team 1 Chose to Bat first
			return true;
		return false;	// Team 2 gets first Batting
	}
	else {	// TAILS
		cout << "\n\nTAILS!!\n";
		_sleep(1000);
		bool choice = tossChoice(tName2);	// Get the Choice of Team which Won the Toss
		
		if (choice)	// Team 2 chose to Bat first
			return false;
		return true;	// Team 1 gets the first Batting
	}
}

bool Game::tossChoice(const string& tName)
{
	cout << endl << tName << " Won the Toss!!\n\n";
	_sleep(2000);


	int input = getNum(tName + ": You want Batting or Bowling(1/2)?\n");	// Get User's choice: a number
	
	while (input != 1 && input != 2) {	// User entered wrong Input
		cout << "\nSorry, wrong input!! Please try again.....\n";
		input = getNum(tName + ": You want Batting or Bowling(1/2)?\n");
	}

	if (input == 1) {	// Chose to Bat first
		cout << "\n\n" << tName << " won the toss and chose to BAT first.....";
		_sleep(2000);

		cout << "\n\n\nStarting the game.....";
		_sleep(2000);
		return true;
	}
	else {		// Chose to Bowl first
		cout << "\n\n" << tName << " won the toss and chose to BOWL first.....";
		_sleep(2000);

		cout << "\n\n\nStarting the game.....";
		_sleep(2000);
		return false;
	}
}

bool Game::areTeamsEligible()
{
	int eligibleTeams = 0;

	for (const Team& team : teams) {
		if (team.canPlay(nWickets, ceil(static_cast<double>(nBalls) / ballsPerOver)))	// Team is eligible
			++eligibleTeams;
	}

	// Teams required for a match: 2
	if (eligibleTeams < 2) {
		cout << "\nNot enough teams to play!!\n\n";
		return false;
	}

	// We have eligible Teams
	return true;
}

void Game::init()
{
	// Reset Game Parameters
	leftWickets = nWickets;
	leftBalls = nBalls;

	// Seed the Randum number generator with current system time in seconds
	time_t currTime;
	time(&currTime);
	srand((unsigned int)currTime);
}
