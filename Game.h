#pragma once
#include <vector>	// NOT REQUIRED
#include <string>	// NOT REQUIRED
#include "Player.h"
#include "Team.h"


const int noOfWickets = 1;
const int noOfBalls = 30;
const int ballsPerOver = 6;

class Game
{
public:
	Game(std::vector<Team>&);
	~Game();

	void play();

private:
	std::vector<Team>& teams;
	int leftWickets;
	int leftBalls;

	void init();
	bool tossChoice(const std::string&);
	bool toss(const std::string&, const std::string&);
	int innings(Team&, Team&);
	int match(Team&, Team&);

	bool areTeamsEligible();
	int posPlayingTeam(const std::string&);
};

