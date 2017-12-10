#include <wx/wxprec.h>
#include "skull.h"

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
		state_ = player;
		if (player == Button::State::Red) {
			SetBackgroundColour(*wxRED);
		}
		else {
			SetBackgroundColour(*wxBLUE);
		}
		//wxWindow* parent = GetParent();
		//TTTBoard* active = (TTTBoard*)parent;
		//active->OnClick
	}
};

void TTTFrame::OnClick(/*wxCommandEvent& event*/) {
	//wxObject* obj = event.GetEventObject();
	//TTTButton* active = (TTTButton*)obj;
	//active->SetBackgroundColour(*wxRED);
	//button1->SetBackgroundColour(*wxBLACK);
}