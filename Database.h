#pragma once
#include <string>	// NOT REQUIRED
#include <vector>	// NOT REQUIRED
#include "Player.h"
#include "Team.h"

using namespace std;

class Database
{
public:
	Database(const string&);
	~Database();

	vector<Team>& getTeams();
	void menu();



private:
	vector<Team> teams;
	string fileName;

	void addPlayer();
	void modifyPlayer();
	void deletePlayer();
	void deleteTeam();
	void display() const;

	void displayTeam(const Team&) const;
	string getTeamName(const string&) const;
	Player getPlayer(const string&, const string&) const;

	void write() const;
	void read();

};
