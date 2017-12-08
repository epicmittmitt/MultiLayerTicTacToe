#pragma once
#include <wx/wxprec.h>
#include "structure.h"

class TTTButton : public Button, public wxButton {
public:
	TTTButton(int position, wxPanel* panel);
};

enum {
	ID_Hello = 1, ID_Panel, ID_Button
};

class TTTBoard : public Grid, public wxPanel {
public:
	TTTBoard(int pos, wxWindow* frame, bool level) : Grid(pos), wxPanel(frame, ID_Panel), grid(nullptr) {
		grid = new wxGridSizer(3, 3, 4, 4);		//Level is a bool because it holds either boards or buttons, not both.
		if (level) {								//True is buttons, false is boards
			for (int index = 0; index < 9; ++index) {
				TTTButton* button = new TTTButton(index, this);
				items_.push_back(button);
				//setItemAtPosition(index, button);
				grid->Add(button, 0, wxEXPAND);
			}
			SetBackgroundColour(*wxWHITE);
		}
		else {
			for (int index = 0; index < 9; ++index) {
				TTTBoard* board = new TTTBoard(index, this, true);
				items_.push_back(board);
				grid->Add(board, 0, wxEXPAND);
			}
			SetBackgroundColour(*wxBLACK);
		}
		SetSizer(grid);
	}
private:
	wxGridSizer* grid;
};

/*class TTTButton : public Button, public wxButton {
public:
	TTTButton(int position, wxPanel* panel) : Button(position, false, Button::State::None), wxButton(panel, -1, wxEmptyString) {}
};*/

TTTButton::TTTButton(int position, wxPanel* panel) : Button(position, false, Button::State::None), wxButton(panel, -1, wxEmptyString) {};


