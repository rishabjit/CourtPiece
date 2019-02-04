#include "GameEngine.h"
#include <stdlib.h>


GameEngine::GameEngine()
{
	players = new Player*[4];
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
		team1.p1->receiveSingleCard(allCards[4 * i]);
		team2.p1->receiveSingleCard(allCards[4 * i + 1]);
		team1.p2->receiveSingleCard(allCards[4 * i + 2]);
		team2.p2->receiveSingleCard(allCards[4 * i + 3]);
	}

}
Player* GameEngine::twoPlayerBet(Player* p1, Player* p2, int *minBet)
{
	Player* toReturn = p2;

	while (*minBet <= 12)
	{
		int p1Raise = p1->placeBet(*minBet);
		if (p1Raise < 0)
			break;
		else if(*minBet <= 12)
		{
			toReturn = p1;
			*minBet = p1Raise + *minBet;
			int p2Raise = p2->placeBet(*minBet);
			if (p2Raise < 0)
				break;
			else
			{
				toReturn = p2;
				*minBet = p2Raise + *minBet;
			}
		}
	}
	return toReturn;
}

// returns if c1 > c2
bool GameEngine::isCardGreater(Card c1, Card c2, tCardType roundSuite, tCardType trumpSuite)
{
	if (c1.type != roundSuite && c2.type != roundSuite && c1.type != trumpSuite && c2.type != trumpSuite)
		throw "Invalid Cards";

	if (c1.type != trumpSuite && c2.type != trumpSuite)
	{
		if (c2.type != roundSuite)
			return true;
		else if (c1.type != roundSuite)
			return false;
		else
			return c1.num > c2.num;
	}
	else
	{
		if (c1.type != trumpSuite)
			return false;
		else if (c2.type != trumpSuite)
			return true;
		else
			return c1.num > c2.num;
	}
}
int GameEngine::playOneRound(int roundNum, std::vector<Card>& roundCards, int lastRoundWinner)
{	 
	int roundWinnerIndex = 0;
	tCardType roundSuite;
	for (int i = 0; i < 4; i++)
	{
		Card playedCard = players[(lastRoundWinner + i) % 4]->playerTurn(roundCards, roundNum);
		roundCards.push_back(playedCard);

		if (roundCards.size() > 1)
		{
			roundWinnerIndex = isCardGreater(playedCard, roundCards[roundWinnerIndex], roundSuite, gameTrump) ? i : roundWinnerIndex;
		}
		else
		{
			roundSuite = roundCards[0].type;
		}
	}
	
	
	//for (int i = 1; i < 4; i++)
	//{
	//	if (isCardGreater(roundCards[i], roundCards[roundWinnerIndex], roundSuite, gameTrump))
	//		roundWinnerIndex = i;
	//}
	return (lastRoundWinner + roundWinnerIndex)%4;
}
void GameEngine::updateScore(int roundWinner)
{
	if (roundWinner % 2 == 0)
	{
		team1.currentScore += 1;
	}
	else
	{
		team2.currentScore += 1;
	}
}
void GameEngine::declareResults(int round, const std::vector<Card>& roundCards, int t1Score, int t2Score)
{
	for (int i = 0; i < 4; i++)
	{
		players[i]->getResults(round, roundCards, t1Score, t2Score);
	}
}
void GameEngine::betting()
{
	Player * betWinner = players[0];
	int minBet = 7;
	for (int i = 1; i < 4; i++)
	{
		betWinner = twoPlayerBet(players[i], betWinner, &minBet);
		std::cout << "Bet winner = " << betWinner->getName() << "with bet " << minBet << "\n";
	}
	gameTrump = betWinner->getTrump();
	
	int winnerIndex = 0;
	for (; winnerIndex < 4; winnerIndex++)
	{
		if (players[winnerIndex] == betWinner)
			break;
	}
	betWinnerIndex = winnerIndex;
	if (winnerIndex % 2 == 0)
	{
		team1.scoreToBeat = minBet;
		team1.p1->setScoretoBeat(minBet);
		team1.p2->setScoretoBeat(minBet);

		team2.scoreToBeat = 13 - minBet + 1;
		team2.p1->setScoretoBeat(13 - minBet + 1);
		team2.p2->setScoretoBeat(13 - minBet + 1);
	}
	else
	{
		team2.scoreToBeat = minBet;
		team2.p1->setScoretoBeat(minBet);
		team2.p2->setScoretoBeat(minBet);

		team1.scoreToBeat = 13 - minBet + 1;
		team1.p1->setScoretoBeat(13 - minBet + 1);
		team1.p2->setScoretoBeat(13 - minBet + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		players[i]->setTrumpCardSuite(gameTrump);
	}
}

void GameEngine::gamePlay()
{
	int roundNum = 0;
	team1.currentScore = 0;
	team2.currentScore = 0;
	int lastRoundWinner = betWinnerIndex;

	while (roundNum < 13)
	{
		std::vector<Card> roundCards;
		lastRoundWinner = playOneRound(roundNum, roundCards, lastRoundWinner);

#if 1
		for (int i = 0; i < roundCards.size(); i++)
			std::cout << roundCards[i] << " ";
		std::cout << "\n";
#endif
		updateScore(lastRoundWinner);

#if 1
		std::cout << "Team 1 Score = " << team1.currentScore << "\n";
		std::cout << "Team 2 Score = " << team2.currentScore << "\n";
#endif
		declareResults(roundNum, roundCards, team1.currentScore, team2.currentScore);
		roundNum++;
	}
	if (team1.currentScore >= team1.scoreToBeat)
		std::cout << "Winner is Team 1 \n";
	else
		std::cout << "Winner is Team 2 \n";


}

GameEngine::~GameEngine()
{
	delete[] players;
}
