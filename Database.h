#pragma once
#include <string>
#include <vector>
#include "Team.h"

using namespace std;

class Database
{
public:
	Database(string);
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

	void displayTeam(Team&);
	string getTeamName(string);

	void write();
	void read();

};
