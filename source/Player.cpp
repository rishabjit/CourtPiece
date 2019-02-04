#include "Player.h"

Card Player::playerTurn(std::vector<Card> currentGameCards)
{
	return Card();
}

int Player::placeBet(int minBet)
{
	return AI->placeBet(minBet, playerCards, &trumpCardSuite);
}

void Player::receiveCards(std::vector<Card> cards)
{
	playerCards = cards;
}
void Player::receiveSingleCard(Card card)
{
	playerCards.push_back(card);
}
void Player::emptyCards()
{
	playerCards.clear();
}
void Player::setTrumpCardSuite(tCardType suite)
{
	trumpCardSuite = suite;
}
void Player::printPlayerCards()
{
	for (int i = 0; i < playerCards.size(); i++)
	{
		std::cout << playerCards[i];
	}
}