#pragma once
#include <string>	// NOT REQUIRED
#include <vector>	// NOT REQUIRED
#include "Player.h"
#include "Team.h"


class Database
{
public:
	Database(const std::string& fileName);
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

	void displayTeam(const Team& team) const;
	std::string getTeamName(const std::string& prompt) const;
	Player getPlayer(const std::string& pName, const std::string& prompt) const;

	void write() const;
	void read();

};
