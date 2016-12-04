#pragma once
#include <string>

using namespace std;

class Player
{
public:
	Player();
	~Player();
	Player(string, int, int, int, int);

	string name;

	double getBattingSkills() const;
	double getBowlingSkills() const;

	void increaseRuns(int);
	void increaseWickets(int);
	void increaseMatches(int);
	void increaseOvers(int);

	void write(ofstream&);
	void read(ifstream&);

	bool operator==(const Player&);
	bool operator!=(const Player&);

private:
	double battingSkills;
	double bowlingSkills;
	int totalRuns;
	int totalWickets;
	int totalMatches;
	int totalOversBowled;

	void setBowlingSkills();
	void setBattingSkills();

	friend bool operator==(const Player&, const Player&);


};

bool operator==(const Player&, const Player&);
bool operator==(const Player& p1, const Player& p2);

namespace std {
	template <> struct hash<Player>
	{
		size_t operator()(const Player & x) const
		{
			return hash<double>()(x.getBattingSkills());
		}
	};
}