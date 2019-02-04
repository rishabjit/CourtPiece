#pragma once
#include "Card.h"
#include "PlayerAI.h"
#include <iostream>
#include <vector>
#include <string>
class Player
{

private:
	tCardType trumpCardSuite;
	std::vector<Card> playerCards;
	PlayerAI *AI;
	std::string name;
public:
	Player(PlayerAI *_AI, std::string _name):AI(_AI), name(_name)
	{

	}
	Card playerTurn(std::vector<Card> currentGameCards);
	int placeBet(int minBet);
	void receiveCards(std::vector<Card> cards);
	void receiveSingleCard(Card card);
	void emptyCards();
	void setTrumpCardSuite(tCardType suite);
	void printPlayerCards();
	tCardType getTrump()
	{
		return trumpCardSuite;
	}
	void setScoretoBeat(int score)
	{
		AI->setScoreToBeat(score);
	}
	std::vector<Card> getCards()
	{
		return playerCards;
	}
	std::string getName()
	{
		return name;
	}
};