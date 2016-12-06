#pragma once
#include <string>	// NOT REQUIRED
#include <vector>	// NOT REQUIRED
#include "Player.h"
#include "Team.h"


class Database
{
public:
	Database(const std::string&);
	~Database();

	std::vector<Team>& getTeams();
	void menu();



private:
	std::vector<Team> teams;
	std::string fileName;

	void addPlayer();
	void modifyPlayer();
	void deletePlayer();
	void deleteTeam();
	void display() const;

	void displayTeam(const Team&) const;
	std::string getTeamName(const std::string&) const;
	Player getPlayer(const std::string&, const std::string&) const;

	void write() const;
	void read();

};
