#include "Player.h"

#include <fstream>	// For ifstream, ofstream

using namespace std;


Player::Player()	// Default Constructor
	: name{ "NOT ENTERED" }, totalMatches{ 0 }, totalOversBowled{ 0 }, totalRuns{ 0 }, totalWickets{ 0 }
{
	setBowlingSkills();
	setBattingSkills();
}
Player::Player(const string& name)	// Parametrized Constructor
	:name{ name }, totalMatches{ 0 }, totalOversBowled{ 0 }, totalRuns{ 0 }, totalWickets{ 0 }
{
	setBowlingSkills();
	setBattingSkills();
}
Player::Player(const string& name, int matches, int overs, int runs, int wickets)	// Overloaded Parameterized Constructor
	: name{ name }, totalMatches{ matches }, totalOversBowled{ overs }, totalRuns{ runs }, totalWickets{ wickets }
{
	setBowlingSkills();
	setBattingSkills();
}

Player::~Player()	// Destructor
{
}


// Public Member Functions

// Getters/ Accessors
double Player::getBattingSkills() const
{
	return battingSkills;
}
double Player::getBowlingSkills() const
{
	return bowlingSkills;
}

// Mutators
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

// Other Functions
void Player::write(ofstream& ofs) const
{
	if (!ofs)
		throw runtime_error("Error writing to File");

	// Write all 5 Details of a Player
	ofs << "(\n" << name << "\n" << totalMatches << "\n" << totalOversBowled << "\n" << totalRuns << "\n" << totalWickets << "\n)\n";
}
void Player::read(ifstream& ifs)
{
	if (!ifs)
		throw runtime_error("Error reading from File");
	
	getline(ifs, name);	// Read the name
	while (name == "")	// Read again if getline terminated because of unread '\n'
		getline(ifs, name);

	// Read all other details separated by endlines
	ifs >> totalMatches >> totalOversBowled >> totalRuns >> totalWickets;

	// If unable to read, i.e., File Buffer if not good
	if (!ifs)
		throw runtime_error("Error reading from File");


	// Set new Batting and Bowling Skills
	setBattingSkills();
	setBowlingSkills();
}


// Private Member Functions
void Player::setBattingSkills()
{
	if (totalMatches == 0) {
		battingSkills = 0;		// 0 Batting Skills if no match is Played
		return;
	}

	// Set batting Skills
	double x = (double)totalRuns / totalMatches;
	battingSkills = 10 * x / (x + 25);

}
void Player::setBowlingSkills()
{
	if (totalOversBowled == 0) {
		bowlingSkills = 0;		// 0 Bowling Skills if no over is Bowled
		return;
	}

	// Set Bowling Skills
	double x = (double)totalWickets * 4 / totalOversBowled;
	bowlingSkills = 10 * x / (x + 0.75);

}




// Operator Overloads for Player
bool operator==(const Player& player1, const Player& player2)
{
	return (player1.name == player2.name);	// Equality based on only the name of Players
}
bool operator!=(const Player& player1, const Player& player2)
{
	return (player1.name != player2.name);	// Inequality based on only the name of Players
}