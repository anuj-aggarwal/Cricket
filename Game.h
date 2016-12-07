#pragma once
#include <vector>	// NOT REQUIRED
#include <string>	// NOT REQUIRED
#include "Player.h"
#include "Team.h"


const int nWickets = 1;
const int nBalls = 30;
const int ballsPerOver = 6;

class Game
{
public:
	Game(std::vector<Team>& teams);
	~Game();

	void play();

private:
	std::vector<Team>& teams;
	int leftWickets;
	int leftBalls;

	void init();
	bool tossChoice(const std::string& tName);
	bool toss(const std::string& tName1, const std::string& tName2);
	int innings(Team& battingTeam, Team& bowlingTeam);
	int match(Team& team1, Team& team2);

	bool areTeamsEligible();
	int posPlayingTeam(const std::string& prompt);
};

