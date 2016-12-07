#pragma once
#include <string>


class Player
{
public:
	Player();
	~Player();
	Player(const std::string& name);
	Player(const std::string& name, int matches, int overs, int runs, int wickets);

	std::string name;

	double getBattingSkills() const;
	double getBowlingSkills() const;

	void increaseMatches(int matches);
	void increaseOvers(int overs);
	void increaseRuns(int runs);
	void increaseWickets(int wickets);

	void write(std::ofstream& ofs) const;
	void read(std::ifstream& ifs);


private:
	double battingSkills;
	double bowlingSkills;
	int totalRuns;
	int totalWickets;
	int totalMatches;
	int totalOversBowled;

	void setBowlingSkills();
	void setBattingSkills();

	friend bool operator==(const Player& player1, const Player& player2);
	friend bool operator!=(const Player& player1, const Player& player2);

};

bool operator==(const Player& player1, const Player& player2);
bool operator!=(const Player& player1, const Player& player2);

namespace std {
	template <> struct hash<Player>
	{
		size_t operator()(const Player & x) const
		{
			return hash<double>()(x.getBattingSkills());
		}
	};
}