#include "PlayerAI.h"
#include <algorithm>
#include <iostream>

PlayerAI::PlayerAI()
{
}


PlayerAI::~PlayerAI()
{
}
struct myclass
{
	bool operator() (Card a, Card b)
	{
		if (a.type < b.type)
			return true;
		else if (a.type == b.type)
		{
			return a.num < b.num;
		}
		return false;
	}
}myobject;
int EasyPlayerAI::placeBet(int minBet, const std::vector<Card> playerCards, tCardType * trump)
{
	std::vector<Card> cards = playerCards;
//	std::sort(cards.begin(), cards.end(), myobject);
	int numEachSuite[] = { 0,0,0,0 };
	for (int i = 0; i < cards.size(); i++)
	{
		numEachSuite[cards[i].type]++;
	}
	int higestinSuite = *std::max_element(&numEachSuite[0], &numEachSuite[4]);
	int highestNum = std::distance(&numEachSuite[0], std::max_element(&numEachSuite[0], &numEachSuite[4]));
	*trump = eCardType(highestNum);
	if (7+(higestinSuite - 3) > minBet)
		return 1;
	else
		return -1;

}

int EasyPlayerAI::playerTurn(const std::vector<Card> currentGameCards, const std::vector<Card> playerCards, const std::vector<int> validCards, tCardType trumpCard)
{
	return validCards[0];
}


int ManualPlayerAI::placeBet(int minBet, const std::vector<Card> playerCards, tCardType * trump)
{
	std::cout << "\n" << "---- Player Cards ---- \n";
	for (int i = 0; i < playerCards.size(); i++)
		std::cout << playerCards[i] << " ";
	std::cout << "\n" << "Current MinBet = "<< minBet << "\n";
	std::cout << "\n" << "Input Increase in bet (-1 for fold)\n";
	int input1,input2;
	std::cin >> input1;
	std::cout << "\n" << "Input Trump (0,1,2 or 3)\n";
	std::cin >> input2;
	*trump = eCardType(input2);
	return input1;
}

int ManualPlayerAI::playerTurn(const std::vector<Card> currentGameCards, const std::vector<Card> playerCards, const std::vector<int> validCards, tCardType trumpCard)
{
	std::cout << "\n" << "---- Player Cards ---- \n";
	for (int i = 0; i < playerCards.size(); i++)
		std::cout << playerCards[i] << " ";
	
	std::cout << "\n" << "---- Game Cards ---- \n";
	for (int i = 0; i < currentGameCards.size(); i++)
		std::cout << currentGameCards[i] << " ";

	std::cout << "\n" << "---- Valid Cards ---- \n";
	for (int i = 0; i < validCards.size(); i++)
		std::cout << validCards[i] << " ";

	std::cout << "\n" << "Game Trump = "<< trumpCard<<"\n";
	std::cout << "\n" << " Choose valid card" << "\n";
	int input;
	std::cin >> input;
	return input;

}
