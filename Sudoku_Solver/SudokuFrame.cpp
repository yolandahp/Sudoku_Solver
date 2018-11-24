#include "SudokuFrame.h"
#include "SudokuWindow.h"
#include "HTPWindow.h"
#include "CreditsWindow.h"
#include "BoardWindow.h"

SudokuFrame::SudokuFrame(const wxString &title) : wxFrame(NULL, wxID_ANY, title) {
	this->InitComponents();
}

void SudokuFrame::InitComponents() {
	boxSizer = new wxBoxSizer(wxVERTICAL);

	this->mainwindow = new SudokuWindow(this);
	this->mainwindow->Show(false);
	this->boxSizer->Add(mainwindow, 1, wxEXPAND, 0);

	this->boardwindow = new BoardWindow(this);
	this->boardwindow->Show(false);
	this->boxSizer->Add(boardwindow, 1, wxEXPAND, 0);

	this->howtoplaywindow = new HTPWindow(this);
	this->howtoplaywindow->Show(false);
	this->boxSizer->Add(howtoplaywindow, 1, wxEXPAND, 0);

	this->creditswindow = new CreditsWindow(this);
	this->creditswindow->Show(false);
	this->boxSizer->Add(creditswindow, 1, wxEXPAND, 0);

	SetSizer(boxSizer);
	ShowMainWindow();
}

void SudokuFrame::ShowMainWindow()
{
	this->mainwindow->Show(true);
	this->howtoplaywindow->Show(false);
	this->creditswindow->Show(false);
	this->boardwindow->Show(false);
	this->fitwindowSize();
}

void SudokuFrame::ShowBoardWindow()
{
	this->mainwindow->Show(false);
	this->howtoplaywindow->Show(false);
	this->creditswindow->Show(false);
	this->boardwindow->Show(true);
	this->fitwindowSize();
}

void SudokuFrame::ShowHTPWindow()
{
	this->mainwindow->Show(false);
	this->howtoplaywindow->Show(true);
	this->creditswindow->Show(false);
	this->boardwindow->Show(false);
	this->fitwindowSize();
}

void SudokuFrame::ShowCreditWindow()
{
	this->mainwindow->Show(false);
	this->howtoplaywindow->Show(false);
	this->creditswindow->Show(true);
	this->boardwindow->Show(false);
	this->fitwindowSize();
}

void SudokuFrame::fitwindowSize()
{
	this->boxSizer->Fit(this);
	this->boxSizer->SetSizeHints(this);
	this->SetSize(wxSize(805, 640));
	this->Layout();
}