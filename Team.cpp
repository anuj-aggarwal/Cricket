#include "Team.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include "Input.h"

using std::cout;
using std::cin;
using std::setw;



Team::Team()
	:name{ "INDIVIDUALS" }
{
}

Team::Team(string nm, vector<Player> newPlayers)
	: name{ nm }, players{ newPlayers }
{
	for (const Player& p : newPlayers) {
		oversBowled.insert(pair<Player, int>(p, 0));
	}
}
Team::Team(string nm)
	: name{ nm }
{
}

Team::~Team()
{
}


bool Team::canBowl(const Player& p)
{
	if (oversBowled[p] >= 4)
		return false;
	return true;
}


void Team::addPlayer(const Player& p)
{
	if (findPos(players, p) != -1)
		return;
	players.push_back(p);
	oversBowled.insert(pair<Player, int>(p, 0));
}

Player* Team::getNextBatsman(vector<Player> & batsmanPlayed)
{
	while (true) {

		displayBatsman();

		string batsman = getString("\nEnter the name of next batsman:\n");

		int batsmanPos = findPos(players, Player(batsman));
		if (batsmanPos == -1) {
			cout << " \nPlayer not found!!\n";
		}
		else if (findPos(out, players[batsmanPos]) != -1) {
			cout << '\n' << batsman << " already out!!\n";
		}
		else {
			batsmanPlayed.push_back(players[batsmanPos]);
			Player* ptrBatsman = &(players[batsmanPos]);
			return ptrBatsman;

		}
	}


}
Player* Team::getNextBowler()
{
	while (true) {

		displayBowler();

		string bowler = getString("\nEnter the name of next bowler:\n");

		int bowlerPos = findPos(players, Player(bowler));
		if (bowlerPos == -1)
			cout << "\nPlayer not found!!\n";
		else if (!canBowl(players[bowlerPos])) {
			cout << '\n' << bowler << " already bowled maximum overs bowled i.e. " << maxOvers << " overs!!\n";
		}
		else {
			oversBowled[players[bowlerPos]]++;
			Player* ptrBowler = &(players[bowlerPos]);
			return ptrBowler;
		}

	}


}


void Team::displayBatsman()
{
	cout << "\n**********  Available Batsmen  **********\n";
	cout << endl << setw(25) << "Batsman Name" << setw(10) << "Skills" << "\n\n";
	for (const Player& p : players) {
		if (findPos(out, p) == -1) {
			cout << setw(25) << p.name << setw(10) << p.getBattingSkills() << '\n';
		}
	}
	cout << "#---------------------------------------#\n";
	cout << endl;
}

void Team::displayBowler() 	// IN PROGRESS
{
	system("cls");
	cout << "***************  Available Bowlers  ***************\n";
	cout << endl << setw(25) << "Bowler Name" << setw(10) << "Skills" << setw(15) << "Overs Bowled"<<"\n\n";
	for (const Player& p : players) {
		if (canBowl(p)) {
			cout << setw(25) << p.name << setw(10) << p.getBowlingSkills() << setw(15) << oversBowled[p] << '\n';
		}
	}
	cout << "#-------------------------------------------------#\n\n";
}

void Team::reset()
{
	out.clear();

	for (const Player& p : players)
		oversBowled[p] = 0;
}

void Team::playerOut(const Player& p)
{
	if (findPos(out, p) != -1)
		return;
	out.push_back(p);
}

bool Team::canPlay(int noOfWickets, int noOfOvers) const
{
	return (players.size() >= noOfWickets && (players.size()*maxOvers) >= noOfOvers);
}

void Team::updateBatsmen(const vector<Player> & batsmanPlayed)
{
	for (const Player& p : batsmanPlayed) {
		int batsmanPos = findPos(players, p);
		if (batsmanPos == -1)
			return;
		players[batsmanPos].increaseMatches(1);

	}
}
void Team::updateBowlers()
{
	for (Player& p : players) {
		p.increaseOvers(oversBowled[p]);
	}
}


void Team::write(ofstream& ofs) const
{
	if (!ofs)
		throw runtime_error("Error writing to File");

	ofs << name << '\n';
	for (const Player& p : players) {
		p.write(ofs);
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
			Player p;
			p.read(ifs);
			temp.push_back(p);
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





bool operator==(const Team& t1, const Team& t2)
{
	return (t1.name == t2.name);
}
bool operator!=(const Team& t1, const Team& t2)
{
	return (t1.name != t2.name);
}