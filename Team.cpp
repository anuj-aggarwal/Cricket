#include "Team.h"

#include <iostream>	// For cout
#include <fstream>	// For ifstream, ofstream
#include <iomanip>	// For setw()

#include "Input.h"	// For getString()

using namespace std;


Team::Team()	// Default Constructor
	:name{ "INDIVIDUALS" }
{
}
Team::Team(string name)	// Initializes players to empty only
	: name{ name }
{
}
Team::Team(string name, vector<Player> newPlayers)
	: name{ name }, players{ newPlayers }
{
	for (const Player& player : newPlayers) {	// Set Overs Bowled of each Player to 0
		oversBowled.insert(pair<Player, int>(player, 0));
	}
}

Team::~Team()	// Destructor
{
}


void Team::addPlayer(const Player& player)
{
	// Assumes Player is not already present
	if (findPos(players, player) != -1)	// Do nothing if player is already present
		return;

	players.push_back(player);
	oversBowled.insert(pair<Player, int>(player, 0));	// Initialize Player's Overs Bowled to 0
}

Player* Team::getNextBatsman(vector<Player> & batsmenPlayed)
{
	while (true) {

		displayBatsmen();

		string batsman = getString("\nEnter the name of next batsman:\n");	// Get name of next Batsman from User through cin

		int posBatsman = findPos(players, Player(batsman));

		if (posBatsman == -1) {
			cout << " \nPlayer not found!!\n";
		}
		else if (findPos(out, players[posBatsman]) != -1) {	// If player is present in out
			cout << '\n' << batsman << " already out!!\n";
		}
		else {
			// If Player is Eligible to Play
			batsmenPlayed.push_back(players[posBatsman]);
			Player* ptrBatsman = &(players[posBatsman]);
			return ptrBatsman;

		}
	}


}
Player* Team::getNextBowler()
{
	while (true) {

		displayBowlers();

		string bowler = getString("\nEnter the name of next bowler:\n");	// Get name of next Batsman from User through cin

		int posBowler = findPos(players, Player(bowler));

		if (posBowler == -1)
			cout << "\nPlayer not found!!\n";

		else if (!canBowl(players[posBowler])) {
			cout << '\n' << bowler << " already bowled maximum overs bowled i.e. " << maxOvers << " overs!!\n";
		}
		else {
			// If Player is Eligible to Bowl Next
			oversBowled[players[posBowler]]++;
			Player* ptrBowler = &(players[posBowler]);
			return ptrBowler;
		}

	}


}

void Team::playerOut(const Player& player)
{
	// Assumes Player is not already out
	if (findPos(out, player) != -1)	// Do nothing if Player is already Out
		return;

	out.push_back(player);
}
bool Team::canPlay(int nWickets, int nOvers) const
{
	// Check if Player has already bowled max Overs allowed
	return (players.size() >= nWickets && (players.size()*maxOvers) >= nOvers);
}

void Team::reset()
{
	out.clear();

	for (const Player& player : players)	// Reset Overs Bowled of all players back to 0
		oversBowled[player] = 0;
}

void Team::updateBatsmen(const vector<Player> & batsmenPlayed)
{
	// Assumes that all player in batsmenPlayed are present in players
	for (const Player& player : batsmenPlayed) {

		int posBatsman = findPos(players, player);
		if (posBatsman == -1)	// Do nothing if Player is not present in players
			return;

		players[posBatsman].increaseMatches(1);

	}
}
void Team::updateBowlers()
{
	for (Player& player : players) {
		player.increaseOvers(oversBowled[player]);
	}
}

void Team::write(ofstream& ofs) const
{
	if (!ofs)
		throw runtime_error("Error writing to File");

	// Write to the File in the specified format
	ofs << name << '\n';
	for (const Player& player : players) {	// Write each player in players
		player.write(ofs);
	}
}
void Team::read(ifstream& ifs)
{
	if (!ifs)
		throw runtime_error("Error reading from File");

	vector<Player> temp;

	getline(ifs, name);

	while (true) {
		char ch;
		ifs >> ch;
		if (ch == '(') {
			Player player;
			player.read(ifs);
			temp.push_back(player);

			// Check if the Player is followed by ')' or not
			ifs >> ch;
			if (ch != ')')	// Wrong Format
				throw runtime_error("Error reading from File");
		}
		else {
			// New Team
			// Place back the first Character of Next Team
			ifs.unget();
			break;
		}
	}

	players = temp;
}




void Team::displayBatsmen()
{
	cout << "\n**********  Available Batsmen  **********\n";

	cout << endl << setw(25) << "Batsman Name" << setw(10) << "Skills" << "\n\n";

	for (const Player& player : players) {	// For each Player in players
		if (findPos(out, player) == -1) {	// If the player is not already out
			// Display name and Batting Skill of the Player
			cout << setw(25) << player.name << setw(10) << player.getBattingSkills() << '\n';
		}
	}

	cout << "#---------------------------------------#\n\n";
}
void Team::displayBowlers()
{
	system("cls");
	cout << "***************  Available Bowlers  ***************\n\n";

	cout << setw(25) << "Bowler Name" << setw(10) << "Skills" << setw(15) << "Overs Bowled" << "\n\n";

	for (const Player& player : players) {	// For each Player in players
		if (canBowl(player)) {
			cout << setw(25) << player.name << setw(10) << player.getBowlingSkills() << setw(15) << oversBowled[player] << '\n';
		}
	}
	cout << "#-------------------------------------------------#\n\n";
}

bool Team::canBowl(const Player& player)
{
	if (oversBowled[player] >= maxOvers)	// If bowler already bowled max Overs
		return false;

	// If Player has not bowled all allowed Overs, he is eligible to bowl
	return true;
}



// Operator Overloads
bool operator==(const Team& team1, const Team& team2)
{
	return (team1.name == team2.name);	// Equality based on name only
}
bool operator!=(const Team& team1, const Team& team2)
{
	return (team1.name != team2.name);	// Inequality based on name only
}