#include "Player.h"
#include <fstream>


Player::Player()
	: name{ "NOT ENTERED" }, totalMatches{ 0 }, totalOversBowled{ 0 }, totalRuns{ 0 }, totalWickets{ 0 }
{
	setBowlingSkills();
	setBattingSkills();
}
Player::~Player()
{
}
Player::Player(const string& nm)
	:name{ nm }, totalMatches{ 0 }, totalOversBowled{ 0 }, totalRuns{ 0 }, totalWickets{ 0 }
{
	setBowlingSkills();
	setBattingSkills();
}
Player::Player(const string& nm, int matches, int overs, int runs, int wickets)
	: name{ nm }, totalMatches{ matches }, totalOversBowled{ overs }, totalRuns{ runs }, totalWickets{ wickets }
{
	setBowlingSkills();
	setBattingSkills();
}


void Player::setBattingSkills()
{
	if (totalMatches == 0) {
		battingSkills = 0;
		return;
	}
	double x = (double)totalRuns / totalMatches;
	battingSkills = 10 * x / (x + 25);

}
void Player::setBowlingSkills()
{
	if (totalOversBowled == 0) {
		bowlingSkills = 0;
		return;
	}
	double x = (double)totalWickets * 4 / totalOversBowled;
	bowlingSkills = 10 * x / (x + 0.75);

}

double Player::getBattingSkills() const
{
	return battingSkills;
}
double Player::getBowlingSkills() const
{
	return bowlingSkills;
}


void Player::increaseMatches(int matches)
{
	totalMatches += matches;
	setBattingSkills();
}
void Player::increaseOvers(int overs)
{
	totalOversBowled += overs;
	setBowlingSkills();
}
void Player::increaseRuns(int runs)
{
	totalRuns += runs;
	setBattingSkills();
}
void Player::increaseWickets(int wickets)
{
	totalWickets += wickets;
	setBowlingSkills();
}


void Player::write(ofstream& ofs) const
{
	if (!ofs)
		throw runtime_error("Error writing to File");

	ofs << "(\n" << name << "\n" << totalMatches << "\n" << totalOversBowled << "\n" << totalRuns << "\n" << totalWickets << "\n)\n";
}
void Player::read(ifstream& ifs)
{
	if (!ifs)
		throw runtime_error("Error reading from File");
	// char ch1, ch2;

	// ifs >> ch1;
	getline(ifs, name);
	while (name == "")
		getline(ifs, name);

	ifs >> totalMatches >> totalOversBowled >> totalRuns >> totalWickets;
	// ifs>> ch2;

	if (!ifs)
		throw runtime_error("Error reading from File");

	// if (ch1 != '(' || ch2 != ')')
	// throw runtime_error("Error reading from File");

	setBattingSkills();
	setBowlingSkills();
}






bool operator==(const Player& p1, const Player& p2)
{
	return (p1.name == p2.name); // && p1.totalMatches == p2.totalMatches && p1.totalOversBowled == p2.totalOversBowled && p1.totalRuns == p2.totalRuns && p1.totalWickets == p2.totalWickets);
}
bool operator!=(const Player& p1, const Player& p2)
{
	return (p1.name != p2.name);
}