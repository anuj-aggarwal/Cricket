#pragma once

#include <string>

// Stores the stats of a Player
// Allows reading the player from a file or write the players stats to the file
class Player
{
public:
	Player();	// Default Constructor
	Player(const std::string& name);	// Constructor to create a Player with given name and 0 stats
	Player(const std::string& name, int matches, int overs, int runs, int wickets);	// Creates a Player with given stats

	~Player();
	
	// DATA MEMBERS
	std::string name;

	// MEMBER FUNCTIONS

	// Getters/ Accessors
	double getBattingSkills() const;
	double getBowlingSkills() const;

	// Mutators
	void increaseMatches(int matches);	
	void increaseOvers(int overs);
	void increaseRuns(int runs);
	void increaseWickets(int wickets);

	// Other Functions
	void write(std::ofstream& ofs) const;	// Writes the details of the Player in the file buffer in a specfic format
											// Throws runtime_error() if File Buffer not in good state

	void read(std::ifstream& ifs);		// Reads the stats of the Player from the file buffer acc. to a specified format 
										// Throws runtime_error() if File Buffer not in good state

	// OPERATOR OVERLOADS
	friend bool operator==(const Player& player1, const Player& player2);
	friend bool operator!=(const Player& player1, const Player& player2);


private:
	// DATA MEMBERS
	double battingSkills;	// Value set by setBattingSkills()
	double bowlingSkills;	// Value set by setBowlingSkills()

	int totalRuns;
	int totalWickets;
	int totalMatches;
	int totalOversBowled;

	// MEMBER FUNCTIONS
	void setBowlingSkills();	// Sets the batting Skills according to total Runs scored and total Matches played by the Batsman
	void setBattingSkills();	// Sets the bowling Skills according to total Wickets taken and total Overs bowled by the Bowler


};



// OPERATOR OVERLOADS
bool operator==(const Player& player1, const Player& player2);	// Equates two Players by their names only
bool operator!=(const Player& player1, const Player& player2);	// Provides negation of equality operator



// Provides a hash to use for map with key as Player
// Takes Batting Skills as the Hashing Element
namespace std {
	template <> struct hash<Player>
	{
		size_t operator()(const Player & x) const
		{
			return hash<double>()(x.getBattingSkills());
		}
	};
}