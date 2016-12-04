#include "Team.h"
#include <iostream>
#include <fstream>
#include <iomanip>

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
	for (Player& p : newPlayers) {
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


bool Team::canBowl(Player& p)
{
	if (oversBowled[p] >= 4)
		return false;
	return true;
}


void Team::addPlayer(Player& p)
{
	if (findPos(players, p) != -1)
		return;
	players.push_back(p);
	oversBowled.insert(pair<Player, int>(p, 0));
}

Player& Team::getNextBatsman(vector<Player> & batsmanPlayed)
{
	while (true) {
		string batsman;
		cout << "\nEnter the name of next batsman:\n";
		displayBatsman();

		getline(cin, batsman);

		while (batsman == "")
			getline(cin, batsman);

		if (!cin)
			throw runtime_error("End of Input received!!\n");

		int batsmanPos = findPos(players, Player(batsman));
		if (findPos(out, players[batsmanPos]) != -1) {
			cout << '\n' << batsman << " already out!!\n";
		}
		else {
			batsmanPlayed.push_back(players[batsmanPos]);
			return players[batsmanPos];

			cout << "\nPlayer not found!!\n";
		}
	}


}
Player& Team::getNextBowler()
{
	while (true) {

		string bowler;
		cout << "\nEnter the name of next bowler:\n";
		displayBowler();

		getline(cin, bowler);

		while (bowler == "")
			getline(cin, bowler);

		if (!cin)
			throw runtime_error("End of Input received!!\n");

		int bowlerPos = findPos(players, Player(bowler));
		if (bowlerPos == -1)
			cout << "\nPlayer not found!!\n";
		else if (!canBowl(players[bowlerPos])) {
			cout << '\n' << bowler << " already bowled maximum overs bowled i.e. " << maxOvers << " overs!!\n";
		}
		else {
			oversBowled[players[bowlerPos]]++;
			return players[bowlerPos];
		}

	}


}


void Team::displayBatsman()
{
	cout << endl << setw(25) << "Batsman Name" << setw(10) << "Skills" << "\n";
	for (Player& p : players) {
		if (findPos(out, p) == -1) {
			cout << setw(25) << p.name << setw(10) << p.getBattingSkills() << '\n';
		}
	}
	cout << endl;
}

void Team::displayBowler()	// IN PROGRESS
{
	cout << endl << setw(25) << "Bowler Name" << setw(10) << "Skills" << setw(15) << "Overs Bowled\n";
	for (Player& p : players) {
		if (canBowl(p)) {
			cout << setw(25) << p.name << setw(10) << p.getBowlingSkills() << setw(15) << oversBowled[p] << '\n';
		}
	}
	cout << endl;
}

void Team::reset()
{
	out.clear();

	for (Player& p : players)
		oversBowled[p] = 0;
}

void Team::playerOut(Player& p)
{
	if (findPos(out, p) != -1)
		return;
	out.push_back(p);
}

bool Team::canPlay(int noOfWickets, int noOfOvers)
{
	return (players.size() >= noOfWickets && (players.size()*maxOvers) >= noOfOvers);
}

void Team::updateBatsmen(const vector<Player> & batsmanPlayed)
{
	for (Player p : batsmanPlayed) {
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


void Team::write(ofstream& ofs)
{
	if (!ofs)
		throw runtime_error("Error writing to File");

	ofs << name << '\n';
	for (Player p : players) {
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




bool Team::operator==(const Team& t) {
	return (name == t.name);
}
bool Team::operator!=(const Team& t) {
	return !(name == t.name);
}