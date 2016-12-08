#pragma once

#include <vector>	// Just for completion of Documentation, Not required, already included in Team.h
#include <string>	// Just for completion of Documentation, Not required, already included in Team.h

#include "Player.h"
#include "Team.h"


const int nWickets = 1;
const int nBalls = 30;
const int ballsPerOver = 6;

// Used for playing the game among any two teams
// Needs to be given a reference of vector of all the teams
// Selection of Batting/Bowling Team, Toss, Evaluating both Innings
//  only Constructor need to be called with teams, and play() to simulate the match
class Game
{
public:

	Game(std::vector<Team>& teams);	// Constructor to initialize its own teams reference to the teams reference passed in constructor
	~Game();	// Destructor

	// MEMBER FUNCTIONS
	void play();	// Match starts by calling this function
					// Decides the two valid teams and simulate the match between them
					// Only function that need to be called for simulation


private:
	// DATA MEMBERS
	std::vector<Team>& teams;
	int leftWickets;
	int leftBalls;

	// MEMBER FUNCTIONS
	void match(Team& team1, Team& team2);	// Simulates match between the two teams given to it
											// Calls innings() to simulate the individual innings but with reverse order of parameters
											// Checks result solely on the Runs scored by the two teams

	int innings(Team& battingTeam, Team& bowlingTeam);	// Simulates the individual innings
														// Runs till all batsmen are out or all balls are over
														// Uses Ball to get result, and do the required based on the Result of each Ball
														// returns the total runs scored by the batting team

	int posPlayingTeam(const std::string& prompt);	// asks for the playing team name from the user
													// loops untill a valid team with sufficient players is received
													// returns the position of the team in the teams vector

	bool toss(const std::string& tName1, const std::string& tName2);	// Simulates Toss between the two teams randomly
																		// Assumes first team has HEADS and second team has TAILS
																		// Calls tossChoice() for team's choice of Batting/Bowling
																		// Returns true if first team is Batting Team, false in reverse case\

	bool tossChoice(const std::string& tName);	// Asks for the teams choice of Batting/ Bowling
												// Returns true if team chooses to Bat first, false, if it chooses to Bowl first

	bool areTeamsEligible();	// Checks whether there are sufficient teams which are eligible to play
								// Eligibility based on Players avalable and required in an Innings for Batting and Bowling

	void init();	// Initializes an Innings by setting left Balls and left Wickets equal to nBalls and nWickets
					// Also acts as the seeder of srand(), seeds srand() by the current system time in seconds.

};