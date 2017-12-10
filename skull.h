#pragma once
#include <wx/wxprec.h>
#include "structure.h"

class TTTproject : public wxApp {
public:
	virtual bool OnInit();
};

class TTTFrame : public wxFrame, public Grid {
public:
	TTTFrame();
	~TTTFrame();
	Button::State getAndSetPlayer();
	void OnClick();
	//void OnClick(wxCommandEvent& event);
private:
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);

	wxGridSizer* grid;
	Button::State player;
};

class TTTButton : public Button, public wxButton {
public:
	TTTButton(int position, int ID, wxPanel* panel);
	void OnClick(wxCommandEvent& event);
};

enum ids{
	ID_Hello = 1, ID_Panel, ID_Button
};

class TTTBoard : public Grid, public wxPanel {
public:
	TTTBoard(int pos, int board, wxWindow* frame) : Grid(pos, (TTTBoard*) frame), wxPanel(frame, ID_Panel), grid(nullptr) {
		grid = new wxGridSizer(3, 3, 4, 4);
		for (int index = 0; index < 9; ++index) {
			string code = to_string(board) + to_string(pos) + to_string(index);
			int passedID = atoi(code.c_str());
			TTTButton* button = new TTTButton(index, passedID, this);
			items_.push_back(button);
			//setItemAtPosition(index, button);
			grid->Add(button, 0, wxEXPAND);
		}
		SetBackgroundColour(*wxWHITE);
		SetSizer(grid);
	}

	TTTBoard(int pos, wxWindow* frame) : Grid(pos, (TTTBoard*) frame), wxPanel(frame, ID_Panel), grid(nullptr) {
		grid = new wxGridSizer(3, 3, 4, 4);
		for (int index = 0; index < 9; ++index) {
			TTTBoard* board = new TTTBoard(index, pos, this);
			items_.push_back(board);
			grid->Add(board, 0, wxEXPAND);
		}
		SetBackgroundColour(*wxBLACK);
		SetSizer(grid);
	}

private:
	wxGridSizer* grid;
};


TTTButton::TTTButton(int position, int ID, wxPanel* panel)
	: Button(position, false, Button::State::None, (TTTBoard*) panel), wxButton(panel, ID, wxEmptyString) {
	Bind(wxEVT_BUTTON, &TTTButton::OnClick, this, ID);
};




