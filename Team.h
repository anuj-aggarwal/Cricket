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
	Team(std::string, std::vector<Player>);
	Team(std::string);
	~Team();

	std::string name;
	std::vector<Player> players;



	void addPlayer(const Player&);
	Player* getNextBatsman(std::vector<Player> &);
	Player* getNextBowler();
	void reset();
	void displayBatsman();
	void displayBowler();
	void playerOut(const Player&);
	bool canPlay(int, int) const;

	void updateBatsmen(const std::vector<Player> &);
	void updateBowlers();

	void write(std::ofstream&) const;
	void read(std::ifstream&);


	friend bool operator==(const Team&, const Team&);
	friend bool operator!=(const Team&, const Team&);

private:

	std::vector<Player> out;
	std::unordered_map<Player, int> oversBowled;

	bool canBowl(const Player&);
};


bool operator==(const Team&, const Team&);
bool operator!=(const Team&, const Team&);

template<class T>
int findPos(std::vector<T>& elements, const T& element)
{
	for (int i = 0; i < elements.size(); ++i) {
		if (element == elements[i])
			return i;
	}
	return -1;
}