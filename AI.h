#ifndef _AI_H_
#define _AI_H_
#include "Gamestate.h"

class AI
{
	Card * hand[13];
	short difficulty;
	public:
	AI(){hand = 0; difficulty = 0;}
	AI(Card**, short);
	
	Card * makePlay(suitLed);
}


#endif //_AI_H_