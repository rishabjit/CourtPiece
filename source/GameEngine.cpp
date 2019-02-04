#include "GameEngine.h"
#include <stdlib.h>


GameEngine::GameEngine()
{
}

void GameEngine::distributeCards()
{
	srand(0);
	std::vector<Card> allCards;
	for (int i = 0; i < 52; i++)
	{
		if (i < 13)
			allCards.push_back(Card(i + 1, HEART));
		else if (i < 26)
			allCards.push_back(Card((i + 1) - 13, SPADE));
		else if (i < 39)
			allCards.push_back(Card(i + 1 - 26, DIAMOND));
		else
			allCards.push_back(Card(i + 1 - 39, CLUB));
	}


	for (int i = 0; i<52; i++)
	{
		// Random for remaining positions. 
		int r = i + (rand() % (52 - i));

		std::iter_swap(allCards.begin() + i, allCards.begin() + r);
	}
	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			players[j]->receiveSingleCard(allCards[j + 4 * i]);
		}

	}

}
Player* GameEngine::twoPlayerBet(Player* p1, Player* p2, int *minBet)
{
	Player* toReturn = p2;

	while (*minBet <= 95)
	{
		int p1Raise = p1->placeBet(*minBet);
		if (p1Raise < 0)
			break;
		else if(*minBet <= 95)
		{
			toReturn = p1;
			*minBet = 5 * p1Raise + *minBet;
			int p2Raise = p2->placeBet(*minBet);
			if (p2Raise < 0)
				break;
			else
			{
				toReturn = p2;
				*minBet = 5 * p2Raise + *minBet;
			}
		}
	}
	return toReturn;
}
void GameEngine::betting()
{
	Player * betWinner = players[0];
	int minBet = 55;
	for (int i = 1; i < 4; i++)
	{
		betWinner = twoPlayerBet(players[i], betWinner, &minBet);
		std::cout << "Bet winner = " << betWinner->getName() << "with bet " << minBet << "\n";
	}
	tCardType finalTrump = betWinner->getTrump();
	
	int winnerIndex = 0;
	for (; winnerIndex < 4; winnerIndex++)
	{
		if (players[winnerIndex] == betWinner)
			break;
	}

	Player* betWinnerTeam[2];
	Player* betLoserTeam[2];

	betWinnerTeam[0] = players[winnerIndex];
	betWinnerTeam[1] = players[(winnerIndex+2)%4];

	betLoserTeam[0] = players[(winnerIndex + 1) % 4];
	betLoserTeam[1] = players[(winnerIndex + 3) % 4];

	for (int i = 0; i < 2; i++)
	{
		betWinnerTeam[i]->setScoretoBeat(minBet);
		betLoserTeam[i]->setScoretoBeat(100-minBet+1);

		betWinnerTeam[i]->setTrumpCardSuite(finalTrump);
		betLoserTeam[i]->setTrumpCardSuite(finalTrump);
	}
}

GameEngine::~GameEngine()
{
}
