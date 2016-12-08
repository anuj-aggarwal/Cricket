#include "Ball.h"

#include <cmath>	// For pow()
#include <random>	// For rand()

using namespace std;

const double e = 2.71828;


Ball::Ball(const Player& batsman, const Player& bowler)
	:batsman{ batsman }, bowler{ bowler }		// Sets own batsman and bowler to batsman and bowler passed 
{
	setResult();
}

Ball::~Ball()
{
}


// PUBLIC MEMBER FUNCTIONS
Result Ball::getResult() const
{
	return result;
}

// PRIVATE MEMBER FUNCTIONS
void Ball::setResult()
{
	// Calculates difference of the two skills, based on which percentages are calculated
	double batsmanSkills = batsman.getBattingSkills();
	double bowlerSkills = bowler.getBowlingSkills();
	double diffSkills = batsmanSkills - bowlerSkills;


	double outperc = 7500 / pow((diffSkills + 20), 2.25);

	double out = (double)95 / 100 * outperc;
	double runOut = (double)5 / 100 * outperc;
	double notOut = 100 - outperc;


	double perc = (double)1000000 / (long long)pow(e, (12 - (0.25)*diffSkills));

	double six = perc / 100 * notOut;
	double four = (perc + 10 - diffSkills) / 100 * (notOut - six);
	double three = (perc + 20 - 2 * diffSkills) / 100 * (notOut - six - four);
	double two = (perc + 30 - 3 * diffSkills) / 100 * (notOut - six - four - three);
	double one = (perc + 40 - 4 * diffSkills) / 100 * (notOut - six - four - three - two);
	double zero = 100 - out - runOut - six - four - three - two - one;


	int randnum = rand() % 100;	// Generate a random number between 0 and 99(inclusive)

	// Sets the result acc. to the random number lying in different ranges of percentages
	if (randnum < zero)
		result = Result::ZERO;
	else if (randnum < zero + one)
		result = Result::ONE;
	else if (randnum < zero + one + two)
		result = Result::DOUBLE;
	else if (randnum < zero + one + two + three)
		result = Result::TRIPLE;
	else if (randnum < zero + one + two + three + four)
		result = Result::FOUR;
	else if (randnum < zero + one + two + three + four + six)
		result = Result::SIX;
	else if (randnum < (100 - runOut))
		result = Result::OUT;
	else
		result = Result::RUNOUT;
}