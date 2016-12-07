#pragma once

#include <string>	// NOT REQUIRED
#include <vector>
#include <unordered_map>


#include "Player.h"

const int maxOvers = 4;

class Team
{

public:
	Team();
	Team(std::string name, std::vector<Player> newPlayers);
	Team(std::string name);
	~Team();

	std::string name;
	std::vector<Player> players;



	void addPlayer(const Player& player);
	Player* getNextBatsman(std::vector<Player>& batsmenPlayed);
	Player* getNextBowler();
	void reset();
	void displayBatsmen();
	void displayBowlers();
	void playerOut(const Player& player);
	bool canPlay(int nWickets, int nOvers) const;

	void updateBatsmen(const std::vector<Player>& batsmenPlayed);
	void updateBowlers();

	void write(std::ofstream& ofs) const;
	void read(std::ifstream& ifs);


	friend bool operator==(const Team& team1, const Team& team2);
	friend bool operator!=(const Team& team1, const Team& team2);

private:

	std::vector<Player> out;
	std::unordered_map<Player, int> oversBowled;

	bool canBowl(const Player& player);
};


bool operator==(const Team& team1, const Team& team2);
bool operator!=(const Team& team1, const Team& team2);



template<class T>
int findPos(std::vector<T>& elements, const T& element)
{
	for (int i = 0; i < elements.size(); ++i) {
		if (element == elements[i])
			return i;
	}
	return -1;
}