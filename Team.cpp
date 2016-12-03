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
	if (find(players.begin(), players.end(), p) != players.end())
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

		cin >> batsman;

		if (!cin)
			throw runtime_error("End of Input received!!\n");

		for (Player& p : players)
			if (p.name == batsman) {
				if (find(out.begin(), out.end(), p) != out.end()) {
					cout << '\n' << batsman << " already out!!\n";
					continue;
				}

				batsmanPlayed.push_back(p);
				return p;
			}
		cout << "\nPlayer not found!!\n";
	}


}
Player& Team::getNextBowler(unordered_map<Player, int> & playersBowled)
{
	while (true) {
		bool flag = false;
		string bowler;
		cout << "\nEnter the name of next bowler:\n";
		displayBowler();

		cin >> bowler;

		if (!cin)
			throw runtime_error("End of Input received!!\n");

		for (Player& p : players)
			if (p.name == bowler) {
				if (!canBowl(p)) {
					cout << '\n' << bowler << " already bowled maximum overs bowled i.e. " << maxOvers << " overs!!\n";
					flag = true;
				}
				else {
					oversBowled[p]++;
					playersBowled = oversBowled;
					return p;
				}
			}
		if (!flag)
			cout << "\nPlayer not found!!\n";
	}


}


void Team::displayBatsman()
{
	cout << endl << setw(25) << "Batsman Name" << setw(10) << "Skills" << "\n";
	for (Player& p : players) {
		if (find(out.begin(), out.end(), p) == out.end()) {
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
	if (find(out.begin(), out.end(), p) != out.end())
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
		for (Player& p1 : players) {
			if (p1 == p)
				p1.increaseMatches(1);
		}
	}
}
void Team::updateBowlers(unordered_map<Player, int> & playersBowled)
{
	for (Player& p : players) {
		p.increaseOvers(playersBowled[p]);
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
	ifs >> name;

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



Team& Team::operator=(const Team& t)
{
	name = t.name;
	players = t.players;

	return *this;
}

bool Team::operator==(const Team& t) {
	return (name == t.name);
}
bool Team::operator!=(const Team& t) {
	return !(name == t.name);
}