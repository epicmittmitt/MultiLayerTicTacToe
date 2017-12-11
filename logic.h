/*
 * logic.cpp
 * This should belong in a main class
 *
 *      Author: connorbeard
 */

#include <iostream>
#include "structure.h"
using namespace std;

vector<Grid*> layers_; // This will be populated with Grid Items
						 // Probably created in some kind of main class where everything starts
void checkForWinner(GridItem *g, GridItem::State s);

/**
 * @param b Button that was just clicked
 * @param s State needed to set the button to. Or whose turn it is
 */
void move(Button *b, GridItem::State s) {
    if (!(b->isLocked()) && b->getState() == GridItem::State::None) {
        b->setState(s);
        b->lock();

        checkForWinner(b, s); // idk why there is an error here
    }
}

/**
 * @param g Any lower level grid item. If this is the top layer (3)
 * 		    then function just returns.
 * @param s State of the specific grid item. Typically this has just changed causing
 * 			there to be new possibilities for winners.
 */
void checkForWinner(GridItem* g, GridItem::State s) {
	// check if top grid
	if (g->getParent() == nullptr)
		return;

	// column win check
	for (int i = g->position() % 3; i < 9; i += 3) {
		if (g->getParent()->getItemAtPosition(i)->getState() != s)
			break;
		if (i >= 6) {
			g->getParent()->setState(s);
			if (g->getParent()->getParent() != nullptr) {
				checkForWinner(g->getParent(), s); // Checks for a winner in the layer above
			}
		}
	}

	// row win check
	for (int i = (g->position()/3) *3; i < (g->position()/3 + 1) *3; i++) {
		if (g->getParent()->getItemAtPosition(i)->getState() != s)
			break;
		if (i >= (g->position()/3) *3 + 2) {
			g->getParent()->setState(s);
			if (g->getParent()->getParent() != nullptr) {
				checkForWinner(g->getParent(), s); // Checks for a winner in the layer above
			}
		}
	}

	// diagonal NW->SE win check
	if (g->position() == 0 || g->position() == 4 || g->position() == 8) {
		for (int i = 0; i < 9; i += 4) {
			if (g->getParent()->getItemAtPosition(i)->getState() != s)
				break;
			if (i == 8) {
				g->getParent()->setState(s);
				if (g->getParent()->getParent() != nullptr) {
					checkForWinner(g->getParent(), s); // Checks for a winner in the layer above
				}
			}
		}
	}

	// diagonal NE->SW win check
	if (g->position() == 2 || g->position() == 4 || g->position() == 6) {
		for (int i = 2; i < 9; i += 2) {
			if (g->getParent()->getItemAtPosition(i)->getState() != s)
				break;
			if (i == 6) {
				g->getParent()->setState(s);
				if (g->getParent()->getParent() != nullptr) {
					checkForWinner(g->getParent(), s); // Checks for a winner in the layer above
				}
			}
		}
	}

	// tie check
	for (int i = 0; i < 9; i++) {
		if (g->getParent()->getItemAtPosition(i)->getState() == GridItem::State::None)
			break;
		if (i == 8)
			g->getParent()->setState(GridItem::State::Tie);
	}
}
