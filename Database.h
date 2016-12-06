#pragma once
#include <string>
#include <vector>
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
	void display();

	void displayTeam(const Team&);
	string getTeamName(const string&);
	Player getPlayer(const string&, const string&);

	void write();
	void read();

};
