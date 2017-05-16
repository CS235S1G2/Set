/***********************************************************************
 * Implementation:
 *    GO FISH
 * Summary:
 *    
 * Author
 *    Nathan Bench, Jed Billman, Jeremy Chandler (Leonel Messi), Justin Chandler
 **********************************************************************/

#include <iostream>     // for ISTREAM, OSTREAM, CIN, and COUT
#include <string>       // for STRING
#include <cassert>      // for ASSERT
#include "goFish.h" 
#include <set> // for DEQUE
using namespace std;


// Verifies if the card drawn is a match with a card in the hand
bool verifyMatch()
{
	if (deck.find(newCard) != deck.end())
	{
		return true;
	}
}

// displays all output
void display()
{
	cout << "round " << roundNumber << ":"; 
	cin >> cardGuess;
	newCard = cardGuess;
	
	// Play game for 5 rounds
	for (roundNumber; roundNumber <= 5; roundNumber++)
	{
		if (verifyMatch())
		{
			numMatches++;
		}
		if (numMatches == 1)
			cout << "You got a match!";
		if (numMatches > 1)
			cout << "Your have " << numMatches << "matches!";
		cout << "The remaining cards: "; // TODO move through the iterator displaying the remaining cards
	}
}

void readFile()
{
	fstream myfile("test.txt");
	if (myfile.is_open())
	{
		while (myfile >> newCard)
			deck.insert(newCard);
	}
	myfile.close();
}

// Main function for the game
void goFish()           // TODO change to goFish()
{
	numMatches = 0;
	roundNumber = 0;
	cout << "We will play 5 rounds of Go Fish. Guess the card in the hand";
	readFile();
	display();
}
