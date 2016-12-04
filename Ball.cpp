#include "Ball.h"
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <random>


const double e = 2.71828;

Ball::~Ball()
{
}

Ball::Ball(Player& abatsman, Player& abowler)
	:batsman{ abatsman }, bowler{ abowler }
{
	setResult();
}



void Ball::setResult()
{
	//// get random value acc. to current system time
	//time_t t;
	//time(&t);
	//srand((unsigned int)t);
	//


	double s1 = batsman.getBattingSkills();
	double s2 = bowler.getBowlingSkills();
	double x = s1 - s2;
	double outperc = 7500 / pow((x + 20), 2.25);

	double out = (double)95 / 100 * outperc;
	double runOut = (double)5 / 100 * outperc;
	double notOut = 100 - outperc;

	double perc = (double)1000000 / (long long)pow(e, (12 - (0.25)*x));

	double six = perc / 100 * notOut;
	double four = (perc + 10 - x) / 100 * (notOut - six);
	double three = (perc + 20 - 2 * x) / 100 * (notOut - six - four);
	double two = (perc + 30 - 3 * x) / 100 * (notOut - six - four - three);
	double one = (perc + 40 - 4 * x) / 100 * (notOut - six - four - three - two);
	double zero = 100 - out - runOut - six - four - three - two - one;



	int randnum = rand() % 100;
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

Result Ball::getResult()
{
	return result;
}