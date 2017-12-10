/*
 * logic.cpp
 * This should belong in a main class
 *
 *      Author: connorgeard
 */

#include<iostream>
#include "structure.h"
using namespace std;

vector<Grid> layers_;

void move(Button b, GridItem::State s) {
	if (!(b.isLocked()) && b.getState() == GridItem::State::None) {
		b.setState(s);
		b.lock();

		checkForWinner(b, s); // idk why there is an error here
	}
}

/**
 * @param g Any lower level grid item. If this is the top layer (3)
 * 		    then function just returns.
 * @param s State of the specific grid item. Typically this has just changed causing
 * 			there to be new possibilities for winners.
 */
void checkForWinner(GridItem g, GridItem::State s) {
	// check if top grid
	if (g.getLayer() == 3)
		return;

	// column win check
	for (int i = g.position() % 3 - 1; i < 9; i += 3) {
		if (layers_.at(g.getLayer() + 1).getItemAtPosition(i).getState() == s)
			break;
		if (i >= 6) {
			g.setState(s);
			checkForWinner(layers_.at(g.getLayer() + 1), s); // Checks for a winner in the layer above
		}
	}

	// row win check
	for (int i = (g.position()/3) *3; i < (g.position()/3 + 1) *3; i++) {
		if (layers_.at(g.getLayer() + 1).getItemAtPosition(i).getState() == s)
			break;
		if (i >= (g.position()/3) *3 + 2) {
			g.setState(s);
			checkForWinner(layers_.at(g.getLayer() + 1), s); // Checks for a winner in the layer above
		}
	}

	// diagonal NW->SE win check
	if (g.position() == 0 || g.position() == 4 || g.position() == 8) {
		for (int i = 0; i < 9; i += 4) {
			if (layers_.at(g.getLayer() + 1).getItemAtPosition(i).getState() == s)
				break;
			if (i == 8) {
				g.setState(s);
				checkForWinner(layers_.at(g.getLayer() + 1), s); // Checks for a winner in the layer above
			}
		}
	}

	// diagonal NE->SW win check
	if (g.position() == 2 || g.position() == 4 || g.position() == 6) {
		for (int i = 0; i < 9; i += 2) {
			if (layers_.at(g.getLayer() + 1).getItemAtPosition(i).getState() == s)
				break;
			if (i == 6) {
				g.setState(s);
				checkForWinner(layers_.at(g.getLayer() + 1), s); // Checks for a winner in the layer above
			}
		}
	}
}
