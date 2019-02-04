#include "Player.h"

Card Player::playerTurn(std::vector<Card> currentGameCards, int roundNum)
{
	std::vector<int> validCards;
	if (currentGameCards.size() != 0)
	{
		tCardType roundSuite = currentGameCards[0].type;
		for (int i = 0; i < playerCards.size(); i++)
			if (playerCards[i].type == roundSuite)
				validCards.push_back(i);
		
	}
	if (validCards.size() == 0)
	{
		for (int i = 0; i < playerCards.size(); i++)
			validCards.push_back(i);
	}
	int playedCard = AI->playerTurn(currentGameCards, playerCards, validCards, trumpCardSuite);
	Card toReturn = playerCards[playedCard];
	playerCards.erase(playerCards.begin() + playedCard);
	return toReturn;
}
void Player::getResults(int round, const std::vector<Card> &roundCards, int t1Score, int t2Score)
{

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