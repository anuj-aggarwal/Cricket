#pragma once

#include <string>	// Just for completion of Documentation, Not required, already included in Player.h
#include <vector>
#include <unordered_map>

#include "Player.h"

const int maxOvers = 4;	// Maximum Overs allowed to a Bowler to bowl in a single Innings


// Stores name and a vector of Players
// Stores all the already out Batsmen and Overs Bowled by each Bowler
// Returns next batsman and bowler asking from the user
// Provides functions to write/read whole Team to/from a file
class Team
{
public:

	Team();	// Default Constructor
	Team(std::string name);	// Parameterized Constructor to initialize name to given name and players to empty vector
	Team(std::string name, std::vector<Player> newPlayers);	// Parametrized Constructor to initialize name and players 

	~Team();	// Destructor

	// Member Functions
	void addPlayer(const Player& player);	// Add the given Player to players
	Player* getNextBatsman(std::vector<Player>& batsmenPlayed);	// Calls displayBatsmen() and asks for batsman name from user
																// Finds the batsman in players
																// repeats untill gets a valid batsman who is not out
																// Returns a reference to the player

	Player* getNextBowler();	// Calls displayBowlers() and asks for bowler name from user
								// Finds the bowler in players, repeats untill gets a valid bowler who can bowl
								// Returns a reference to the player

	void playerOut(const Player& player);	// Declares the given Player to be out, assumes player not already out(does nothing if it is)
	bool canPlay(int nWickets, int nOvers) const;	// Checks if the Team has sufficient players to play
													// Based on nWickets, nOvers, maxOvers

	void reset();	// Clears out, sets Overs bowled by each Bowler to 0

	void updateBatsmen(const std::vector<Player>& batsmenPlayed);	// Increases total Matches of all batsmen who played by 1
	void updateBowlers();	// Increases total Overs of all Bowlers who bowled by no. of Overs Bowled

	void write(std::ofstream& ofs) const;	// Adds Team name and all Players to the file Buffer in a specified format
	void read(std::ifstream& ifs);	// Reads name of team and all Players from the File Buffer in a specified format


	// Operator Overloads
	friend bool operator==(const Team& team1, const Team& team2);
	friend bool operator!=(const Team& team1, const Team& team2);


	// Data Members
	std::string name;
	std::vector<Player> players;


private:
	// Data Members
	std::vector<Player> out;
	std::unordered_map<Player, int> oversBowled;

	// Member Functions
	void displayBatsmen();	// Display all Players who can Bat next
	void displayBowlers();	// Display all Players who can Bowl next
	bool canBowl(const Player& player);	// Checks if a given Player is eligible to bowl or not, i.e. if he has already bowled maxOvers or not
};


// Operator Overloads
bool operator==(const Team& team1, const Team& team2);	// Equality Based on Team Name only
bool operator!=(const Team& team1, const Team& team2);	// Inequality, acts as a negation to Equality Operator



// HELPER FUNCTIONS
template<class T>
int findPos(std::vector<T>& elements, const T& element)	// Returns the position of an element in a vector of elements
														// Returns -1 if the element is not present.
{
	for (int i = 0; i < elements.size(); ++i) {
		if (element == elements[i])
			return i;
	}
	return -1;
}