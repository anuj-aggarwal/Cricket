#pragma once
#include <vector>
#include <string>
#include "Team.h"

using namespace std;

const int noOfWickets = 1;
const int noOfBalls = 30;
const int ballsPerOver = 6;

class Game
{
public:
	Game(vector<Team>&);
	~Game();

	void play();

private:
	vector<Team>& teams;
	int leftWickets;
	int leftBalls;

	void init();
	bool tossChoice(const string&);
	bool toss(const string&, const string&);
	int innings(Team&, Team&);
	int match(Team&, Team&);

	bool areTeamsEligible();
	int posPlayingTeam(const string&);
};

