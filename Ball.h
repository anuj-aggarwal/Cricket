#pragma once
#include "Player.h"
#include "Result.h"

class Ball
{
public:
	Ball(Player&, Player&);
	Ball(const Ball&);
	~Ball();

	Result getResult();


private:
	Player batsman;
	Player bowler;
	Result result;

	void setResult();

};