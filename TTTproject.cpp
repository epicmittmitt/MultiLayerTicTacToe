#include <wx/wxprec.h>
#include "skull.h"

wxIMPLEMENT_APP(TTTproject);
bool TTTproject::OnInit() { TTTFrame *frame = new TTTFrame();    frame->Show(true);    return true; }
TTTFrame::TTTFrame()
	: wxFrame(NULL, wxID_ANY, "Fractalized Tic Tac Toe: Level Three"), Grid(), grid(nullptr) {

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

/*void TTTFrame::OnClick(wxCommandEvent& event) {
	wxObject* obj = event.GetEventObject();
	TTTButton* active = (TTTButton*)obj;
	active->SetBackgroundColour(*wxRED);
	//button1->SetBackgroundColour(*wxBLACK);
}*/
