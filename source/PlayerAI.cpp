#include "PlayerAI.h"
#include <algorithm>


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

	if (55+5*(higestinSuite - 3) > minBet)
		return 1;
	else
		return -1;

}

int EasyPlayerAI::playerTurn(const std::vector<Card> currentGameCards, const std::vector<Card> playerCards, int * validCards)
{
	return 0;
}
