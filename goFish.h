/***********************************************************************
 * Header:
 *    GO FISH
 * Summary:
 *    
 * Author
 *    Nathan Bench, Jed Billman, Justin Chandler, Jeremy Chandler (Leonel Messi)
 ************************************************************************/

#ifndef GO_FISH_H
#define GO_FISH_H

#include <set> // for SET
#include "card.h"
#include <fstream>
 /*****************************************
 * GO FISH
 *****************************************/
void goFish();
bool verifyMatch();
void display();
int numMatches;
int roundNumber;


#endif // GO_FISH_H

