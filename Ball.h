#pragma once
#include "Player.h"
#include "Result.h"

class Ball
{
public:
	Ball(const Player& batsman, const Player& bowler);
	~Ball();

	Result getResult() const;


private:
	Player batsman;
	Player bowler;
	Result result;

	void setResult();

};