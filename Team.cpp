#include "Team.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include "Input.h"

using namespace std;



Team::Team()
	:name{ "INDIVIDUALS" }
{
}

Team::Team(string name, vector<Player> newPlayers)
	: name{ name }, players{ newPlayers }
{
	for (const Player& player : newPlayers) {
		oversBowled.insert(pair<Player, int>(player, 0));
	}
}
Team::Team(string name)
	: name{ name }
{
}

Team::~Team()
{
}


bool Team::canBowl(const Player& player)
{
	if (oversBowled[player] >= 4)
		return false;
	return true;
}


void Team::addPlayer(const Player& player)
{
	if (findPos(players, player) != -1)
		return;
	players.push_back(player);
	oversBowled.insert(pair<Player, int>(player, 0));
}

Player* Team::getNextBatsman(vector<Player> & batsmenPlayed)
{
	while (true) {

		displayBatsmen();

		string batsman = getString("\nEnter the name of next batsman:\n");

		int posBatsman = findPos(players, Player(batsman));
		if (posBatsman == -1) {
			cout << " \nPlayer not found!!\n";
		}
		else if (findPos(out, players[posBatsman]) != -1) {
			cout << '\n' << batsman << " already out!!\n";
		}
		else {
			batsmenPlayed.push_back(players[posBatsman]);
			Player* ptrBatsman = &(players[posBatsman]);
			return ptrBatsman;

		}
	}


}
Player* Team::getNextBowler()
{
	while (true) {

		displayBowlers();

		string bowler = getString("\nEnter the name of next bowler:\n");

		int posBowler = findPos(players, Player(bowler));
		if (posBowler == -1)
			cout << "\nPlayer not found!!\n";
		else if (!canBowl(players[posBowler])) {
			cout << '\n' << bowler << " already bowled maximum overs bowled i.e. " << maxOvers << " overs!!\n";
		}
		else {
			oversBowled[players[posBowler]]++;
			Player* ptrBowler = &(players[posBowler]);
			return ptrBowler;
		}

	}


}


void Team::displayBatsmen()
{
	cout << "\n**********  Available Batsmen  **********\n";
	cout << endl << setw(25) << "Batsman Name" << setw(10) << "Skills" << "\n\n";
	for (const Player& player : players) {
		if (findPos(out, player) == -1) {
			cout << setw(25) << player.name << setw(10) << player.getBattingSkills() << '\n';
		}
	}
	cout << "#---------------------------------------#\n";
	cout << endl;
}

void Team::displayBowlers() 	// IN PROGRESS
{
	system("cls");
	cout << "***************  Available Bowlers  ***************\n";
	cout << endl << setw(25) << "Bowler Name" << setw(10) << "Skills" << setw(15) << "Overs Bowled"<<"\n\n";
	for (const Player& player : players) {
		if (canBowl(player)) {
			cout << setw(25) << player.name << setw(10) << player.getBowlingSkills() << setw(15) << oversBowled[player] << '\n';
		}
	}
	cout << "#-------------------------------------------------#\n\n";
}

void Team::reset()
{
	out.clear();

	for (const Player& player : players)
		oversBowled[player] = 0;
}

void Team::playerOut(const Player& player)
{
	if (findPos(out, player) != -1)
		return;
	out.push_back(player);
}

bool Team::canPlay(int nWickets, int nOvers) const
{
	return (players.size() >= nWickets && (players.size()*maxOvers) >= nOvers);
}

void Team::updateBatsmen(const vector<Player> & batsmanPlayed)
{
	for (const Player& player : batsmanPlayed) {
		int posBatsman = findPos(players, player);
		if (posBatsman == -1)
			return;
		players[posBatsman].increaseMatches(1);

	}
}
void Team::updateBowlers()
{
	for (Player& player : players) {
		player.increaseOvers(oversBowled[player]);
	}
}


void Team::write(ofstream& ofs) const
{
	if (!ofs)
		throw runtime_error("Error writing to File");

	ofs << name << '\n';
	for (const Player& player : players) {
		player.write(ofs);
	}
}
void Team::read(ifstream& ifs)
{
	if (!ifs)
		throw runtime_error("Error reading from File");
	vector<Player> temp;
	getline(ifs, name);

	while (true) {
		char ch;
		ifs >> ch;
		if (ch == '(') {
			Player player;
			player.read(ifs);
			temp.push_back(player);
			ifs >> ch;
			if (ch != ')')
				throw runtime_error("Error reading from File");
		}
		else {
			ifs.unget();
			break;
		}
	}

	players = temp;
}





bool operator==(const Team& team1, const Team& team2)
{
	return (team1.name == team2.name);
}
bool operator!=(const Team& team1, const Team& team2)
{
	return (team1.name != team2.name);
}