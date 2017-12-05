#include "Gamestate.h"
using namespace std;

Gamestate::Gamestate()
{
  score[0] = score[1] = 0;
  turn = p1;
  for(int i = 0; i < 52; ++i){
    cards[i] = 0;
  }
  for(int i = 0; i < 4; ++i){
    hands[i] = new Hand;
  }
}
/*
Number identifier of save game
Scores
turn
Hands (suit and value of cards separated by newlines)
*/

void Gamestate::save_game(int num_save_game)
{
	Card * cardInHand;
	ofstream savefile ("saves.txt", std::fstream::app);
	if (savefile.is_open())
	{
		//allocate an address (greater than 15)
		savefile << num_save_game << endl;
		//save scores
		savefile << score[0] <<" "<< score[1] << endl;
		//save whose turn
		savefile << turn << endl;
		int numCardsInHand;
		
		//save hands 
		//--- 
		//number of cards in hand
		//suit value
		//---
		for(int currenthand = 0; currenthand < 4; ++currenthand)
		{ 
			numCardsInHand = hands[currenthand]->getLen();
			savefile << numCardsInHand << endl;
			for(int currentcard = 0; currentcard < numCardsInHand; ++currentcard)
			{
				cardInHand = hands[currenthand]->getCard(currentcard);
				savefile << cardInHand->get_suit() <<" ";
				savefile << cardInHand->get_val() << endl;
			}
			savefile << endl;
		}
		savefile.close();		
	}
	else
	{
		cout << "Invalid save location." << endl;
		return;
	}
}

void Gamestate::load_game(int num_load_game)
{
  //opens a file
        bool loading = true;
	ifstream loadfile;
	int save_id, numCardsInHand, card_val, card_suit;
	char whosTurn;
	Card * newCard;
	loadfile.open("saves.txt");
	if(!loadfile)
	{
		cout << "Invalid load location." << endl;
		return;
	}
	//No idea if this will work on the first try.
	while(loading)
	{
		loadfile >> save_id;
		if(save_id == num_load_game)
		{
			//load scores
			loadfile >> score[0]; loadfile >> score[1];
			//load turn
			loadfile >> whosTurn;
			//load hands
			for(int currenthand = 0; currenthand < 4; currenthand++)
			{
				loadfile >> numCardsInHand;
				for(int currentcard = 0; currentcard < numCardsInHand; currentcard++)
				{
					loadfile >> card_suit;
					loadfile >> card_val;
					newCard = new Card(card_val, card_suit);
					hands[currenthand]->addCard(newCard);
					
				}
			}
			loadfile.close();
			loading = false;
		}
		else loadfile >> save_id;
	}
}

void Gamestate::deal()
{
        deck.shuffle();
	for(int i = 0; i < 52; ++i){
	  cards[i] = deck.getCard(i);
	}
	for(int i = 0; i < 13; ++i)
	{
		hands[0]->addCard(cards[i]);
	}
	for(int i = 13; i < 26; ++i)
	{
		hands[1]->addCard(cards[i]);
	}
	for(int i = 26; i < 39; ++i)
	{
	  hands[2]->addCard(cards[i]);
	}
	for(int i = 39; i < 52; ++i)
	{
	  hands[3]->addCard(cards[i]);
	}
}
