#pragma once
#include "Player.h"
#include "Result.h"

class Ball
{
public:
	Ball(const Player&, const Player&);
	~Ball();

	Result getResult() const;


private:
	Player batsman;
	Player bowler;
	Result result;

	void setResult();

};