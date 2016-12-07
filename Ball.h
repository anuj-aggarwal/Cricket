#pragma once

#include "Player.h"
#include "Result.h"


// Stores the batsman and bowler
// Calculates percentage of each Result possible acc. to Batsman's and Bowler's Skills
// Generates the result and return it when asked
class Ball
{
public:

	Ball(const Player& batsman, const Player& bowler);	// Constructor to take batsman and bowler and call setResult()
	~Ball();

	// MEMBER FUNCTIONS
	Result getResult() const;	// Getter/ Accessor to get the Result


private:
	// DATA MEMBERS
	Player batsman;
	Player bowler;
	Result result;	// Stores the result of the Ball


	// MEMBER FUNCTIONS
	void setResult();	// Sets the result according to the skills of batsman and bowler

};