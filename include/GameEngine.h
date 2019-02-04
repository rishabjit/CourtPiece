#pragma once
#include "Card.h"
#include "Player.h"
#include <cstdlib>
#include <algorithm>
class GameEngine
{

private:
	Player ** players;
	Player* twoPlayerBet(Player* p1, Player* p2, int *minBet);
public:
	GameEngine();
	void setPlayerArray(Player** _players)
	{
		players = _players;
	}
	void distributeCards();
	void betting();

	~GameEngine();
};

