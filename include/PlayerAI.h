#pragma once
#include "Card.h"
#include <vector>
class PlayerAI
{
private:
	tCardType trump;
	int scoreToBeat;
public:
	virtual int placeBet(int minBet, const std::vector<Card> playerCards, tCardType *trump) = 0;
	virtual int playerTurn(const std::vector<Card> currentGameCards, const std::vector<Card> playerCards, int *validCards) = 0;
	void setTrump(tCardType _trump)
	{
		trump = _trump;
	}
	void setScoreToBeat(int score)
	{
		scoreToBeat = score;
	}
	PlayerAI();
	~PlayerAI();
};
class EasyPlayerAI: public PlayerAI
{
public:
	int placeBet(int minBet, const std::vector<Card> playerCards, tCardType *trump);
	int playerTurn(const std::vector<Card> currentGameCards, const std::vector<Card> playerCards, int *validCards);

};

