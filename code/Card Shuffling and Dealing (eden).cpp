 #include "card.hpp"

using namespace std;

const char* faceNames[totalFaces] = { "Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};
const char* suitNames[totalSuits] = {"Hearts", "Diamonds", "Clubs", "Spades"};

Card::Card(int cardFace, int cardSuit){
	face = cardFace;
	suit = cardSuit;
}

string Card::toString() const{
	string str, str1;
	str1 = " of ";
	str = faceNames[face] + str1 + suitNames[suit];
return str;
}

int Card::getFace() const{
	return face;
}

int Card::getSuit() const{
	return suit;
}


#include "card.hpp"
#include "deck-of-cards.hpp"


DeckOfCards::DeckOfCards(){
	currentCard = 0;
    for(int i = 0; i < 4; i++)
    {
    	for(int j = 0; j < 13; j++)
    	{
    		Card card(j, i);
    		deck.push_back(card);
		}
	}
}

Card DeckOfCards::dealCard(){
	return deck[currentCard++];
}

bool DeckOfCards::moreCards() const{
	if(currentCard < 52)
	{
		return true;
	}
	return false;
}
