#pragma once

#include <string>
#include <vector>
#include <unordered_map>


#include "Player.h"

const int maxOvers = 4;

class Team
{

public:
	Team();
	Team(string, vector<Player>);
	Team(string);
	~Team();

	string name;
	vector<Player> players;



	void addPlayer(Player&);
	Player* getNextBatsman(vector<Player> &);
	Player* getNextBowler();
	void reset();
	void displayBatsman();
	void displayBowler();
	void playerOut(Player&);
	bool canPlay(int, int);

	void updateBatsmen(const vector<Player> &);
	void updateBowlers();

	void write(ofstream&);
	void read(ifstream&);


	bool operator==(const Team&);
	bool operator!=(const Team&);


private:

	vector<Player> out;
	unordered_map<Player, int> oversBowled;

	bool canBowl(Player&);
};





template<class T>
int findPos(vector<T>& elements, T& element)
{
	for (int i = 0; i < elements.size(); ++i) {
		if (element == elements[i])
			return i;
	}
	return -1;
}