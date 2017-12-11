#include <wx/wxprec.h>
#include "skull.h"
#include "logic.h"

wxIMPLEMENT_APP(TTTproject);
bool TTTproject::OnInit() { TTTFrame *frame = new TTTFrame();    frame->Show(true);    return true; }
TTTFrame::TTTFrame()
	: wxFrame(NULL, wxID_ANY, "Fractalized Tic Tac Toe: Level Three"), Grid(), grid(nullptr), player(Button::State::Red) {

	wxMenu *menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT);
	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append(menuHelp, "&Help");
	SetMenuBar(menuBar);

	//panel = new wxPanel(this, ID_Panel, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	//panel->SetBackgroundColour(*wxCYAN);

	grid = new wxGridSizer(3, 3, 8, 8);

	for (int index = 0; index < 9; ++index) {
		TTTBoard* element = new TTTBoard(index, this);
		items_.push_back(element);
		//setItemAtPosition(index, element);
		grid->Add(element, 0, wxEXPAND);
	}
	SetBackgroundColour(*wxLIGHT_GREY);

	wxSize temp(600, 600);
	SetSize(temp);

	wxPoint temp2(0, 0);
	SetPosition(temp2);

	//grid->Add(new wxButton(this, -1, wxT("8")), 0, wxEXPAND);
	//this, -1, wxT("7")), 0, wxEXPAND
	//button->SetBackgroundColour(*wxRED);
	//grid->Add(button, 0, wxEXPAND);

	SetSizer(grid);

	Bind(wxEVT_MENU, &TTTFrame::OnAbout, this, wxID_ABOUT);
	Bind(wxEVT_MENU, &TTTFrame::OnExit, this, wxID_EXIT);
	//Bind(wxEVT_BUTTON, &TTTFrame::OnClick, this, ID_Button);
}

TTTFrame::~TTTFrame() {
	//delete grid;
}

void TTTFrame::OnExit(wxCommandEvent& event) {
	Close(true);
}

void TTTFrame::OnAbout(wxCommandEvent& event) {
	wxMessageBox("This is a wxWidgets' Hello world sample",
		"About Hello World", wxOK | wxICON_INFORMATION);
}

Button::State TTTFrame::getAndSetPlayer() {
	Button::State old = player;
	if (player == Button::State::Red) {
		player = Button::State::Blue;
	}
	else {
		player = Button::State::Red;
	}
	return old;
}

void TTTButton::OnClick(wxCommandEvent& event) {
	//Code only usable with TTTFrame; I'm mostly trying to create generic code, but a user would need to modify this
	if (!locked_ && state_ == Button::State::None) {
		wxWindow* window = GetGrandParent()->GetParent();
		TTTFrame* game = (TTTFrame*)window;
		Button::State player = game->getAndSetPlayer();
		move(this, player);
		//state_ = player;
		if (player == Button::State::Red) {
			SetBackgroundColour(*wxRED);
		}
		else {
			SetBackgroundColour(*wxBLUE);
		}

		game->victory();
		//int id = GetId();
		//Pass to Frame, where parsed and applied.  Remember bouncing off of locked board.
	}
}

void TTTFrame::victory() {
	bool win = false;
	//Row
	for (int index = 0; index < 9; index += 3) {
		if (items_[index]->getState() == items_[index + 1]->getState() && items_[index]->getState() == items_[index + 2]->getState() && items_[index]->getState() != State::Tie && items_[index]->getState() != State::None) {
			setState(items_[index]->getState());
			win = true;
			if (state_ == State::Red) {
				SetBackgroundColour(*wxRED);
				Refresh();
				Update();
			}
			if (state_ == State::Blue) {
				SetBackgroundColour(*wxBLUE);
				Refresh();
				Update();
			}
		}
	}

	//Col
	for (int index = 0; index < 3; index += 1) {
		if (items_[index]->getState() == items_[index + 3]->getState() && items_[index]->getState() == items_[index + 6]->getState() && items_[index]->getState() != State::Tie && items_[index]->getState() != State::None) {
			setState(items_[index]->getState());
			win = true;
			if (state_ == State::Red) {
				SetBackgroundColour(*wxRED);
				Refresh();
				Update();
			}
			if (state_ == State::Blue) {
				SetBackgroundColour(*wxBLUE);
				Refresh();
				Update();
			}
		}
	}

	//Diag TL
	if (items_[0]->getState() == items_[4]->getState() && items_[0]->getState() == items_[8]->getState() && items_[0]->getState() != State::Tie && items_[0]->getState() != State::None) {
		setState(items_[0]->getState());
		win = true;
		if (state_ == State::Red) {
			SetBackgroundColour(*wxRED);
			Refresh();
			Update();
		}
		if (state_ == State::Blue) {
			SetBackgroundColour(*wxBLUE);
			Refresh();
			Update();
		}
	}

	//Diag TR
	if (items_[2]->getState() == items_[4]->getState() && items_[2]->getState() == items_[6]->getState() && items_[2]->getState() != State::Tie && items_[2]->getState() != State::None) {
		setState(items_[2]->getState());
		win = true;
		if (state_ == State::Red) {
			SetBackgroundColour(*wxRED);
			Refresh();
			Update();
		}
		if (state_ == State::Blue) {
			SetBackgroundColour(*wxBLUE);
			Refresh();
			Update();
		}
	}

	if (!win) {
		bool tie = true;
		for (int index = 0; index < 9; ++index) {
			if (items_[index]->getState() == State::None) {
				tie = false;
				break;
			}
		}
		if (tie) {
			setState(State::Tie);
			SetBackgroundColour(*wxCYAN);
			Refresh();
			Update();
		}
	}
}

void TTTFrame::OnClick(/*wxCommandEvent& event*/) {
	//wxObject* obj = event.GetEventObject();
	//TTTButton* active = (TTTButton*)obj;
	//active->SetBackgroundColour(*wxRED);
	//button1->SetBackgroundColour(*wxBLACK);
}
