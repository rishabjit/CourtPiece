#pragma once
#include "Card.h"
#include "Player.h"
#include <cstdlib>
#include <algorithm>
class GameEngine
{

private:
	PlayerTeam team1;
	PlayerTeam team2;
	Player **players;
	Player* twoPlayerBet(Player* p1, Player* p2, int *minBet);
	int playOneRound(int round, std::vector<Card> &roundCards, int lastRoundWinner);
	void updateScore(int roundWinner);
	void declareResults(int round, const std::vector<Card> &roundCards, int t1Score, int t2Score);
	int betWinnerIndex;
	tCardType gameTrump;
	bool isCardGreater(Card c1, Card c2, tCardType roundSuite, tCardType trumpSuite);
public:
	GameEngine();
	void setPlayerArray(Player** _players)
	{
		team1.p1 = _players[0];
		team1.p2 = _players[2];
		team2.p1 = _players[1];
		team2.p2 = _players[3];

		for (int i = 0; i < 4; i++)
			players[i] = _players[i];
	}
	void distributeCards();
	void betting();
	void gamePlay();
	~GameEngine();
};

