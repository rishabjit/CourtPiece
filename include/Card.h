#pragma once
#include <iostream>
typedef enum eCardType
{
	HEART,
	SPADE,
	DIAMOND,
	CLUB,
	DEFAULT
} tCardType;

class Card
{
public:
	int num;
	tCardType type;
	Card()
	{
		num = -1;
		type = DEFAULT;
	}
	Card(int _num, tCardType _type):num(_num),type(_type)
	{

	}
};

static std::ostream & operator <<(std::ostream &out, Card card)
{
	out << "\"";
	out << card.num;
	switch (card.type)
	{
		case(HEART):
			out << "H";
			break;
		case(SPADE):
			out << "S";
			break;
		case(DIAMOND):
			out << "D";
			break;
		case(CLUB):
			out << "C";
			break;
		default:
			throw "Invalid Card\n";
	}
	out << "\" ";
	return out;
}
