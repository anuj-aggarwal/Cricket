#pragma once

#include <string>	// Just for completion of Documentation, Not required, already included in Team.h
#include <vector>	// Just for completion of Documentation, Not required, already included in Team.h

#include "Player.h"
#include "Team.h"


// Loads all the Game Data from the file
// Writes all the Game data to file at the end, with all modifications
// Provides function like Add Player, Modify Player, Delete Player, Display Players, etc to change te Player Database
class Database
{
public:

	Database(const std::string& fileName);	// Constructor to initialize file name containing all the Game Data
											// Checks if the given file name exists or not
											// Calls read() to read all the data into teams vector

	~Database();	// Destructor
					// Calls write when the scope of the Database if Over
					// Writes all Data to the file when the Database no more exists


	// MEMBER FUNCTIONS
	std::vector<Team>& getTeams();	// Getter/ Accessor
									// Returns a reference to the original Teams

	void menu();	// Displays the menu, gets User's choice
					// Calls appropriate functions according to user's choice


private:
	// DATA MEMBERS
	std::vector<Team> teams;	// Acts as the Game Dtaabase storing all the Information of the Game locally
								// Provides fast manipulation instead of reading/writing from/to file for every modification

	std::string fileName;	// Stores name of file containing all the data


	// MEMBER FUNCTIONS
	void display() const;	// Diplays the Details of all the Players and Teams in the Database
	void addPlayer();	// Used to add a Player to an Already existing team, or Create a new Team for the Player
	void modifyPlayer();	// Used to modify the Details of an already existing Player, except his name
	void deletePlayer();	// Used to delete an already existing player
	void deleteTeam();	// Used to delete the whole Team with al the Players

	void displayTeam(const Team& team) const;	// Used to display the Players in the Team given, their Batting Skills and Bowling Skills

	std::string getTeamName(const std::string& prompt) const;	// Gets the Team Name from the user, untill user enters a valid Team
																// Displays the names of all teams present

	Player getPlayer(const std::string& pName, const std::string& prompt) const;	// Gets the Details of a player from User
																	// Checks for the Details to be positive or not using getPositiveNum()
																	// Returns a Player with name same as pName and Details given by User

	void write() const;	// Writes all the Data in the file, named fileName, in a specified format
						// Called when the scope of the Database gets Over by the Destructor
						// Throws runtime_error() if File Buffer is not in good state

	void read();	// Reads all the Data from fileName in a specified Format
					// Throws runtime_error() if File Buffer is not in good state or not in specified format

};
