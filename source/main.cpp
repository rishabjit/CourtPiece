#include <iostream>
#include <vector>

#include "Player.h"
#include "GameEngine.h"

struct myclass1
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
}myobject1;

void printCards(std::vector<Card> playerCards)
{
	for (int i = 0; i < playerCards.size(); i++)
	{
		std::cout << playerCards[i];
	}
	std::cout << std::endl;
}

int main()
{
	EasyPlayerAI AI;
	Player player1(&AI, "p1");
	Player player2(&AI, "p2");
	Player player3(&AI, "p3");
	Player player4(&AI, "p4");
	Player *players[4];
	players[0] = &player1;
	players[1] = &player2;
	players[2] = &player3;
	players[3] = &player4;
	

	GameEngine engine;
	engine.setPlayerArray(players);
	engine.distributeCards();
	for (int i = 0; i < 4; i++)
	{
		players[i]->printPlayerCards();
		std::cout << "\n";
	}
	engine.betting();

	

}