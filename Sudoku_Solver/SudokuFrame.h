#pragma once
#include "wx\wx.h"

class SudokuWindow;
class HTPWindow;
class CreditsWindow;
class BoardWindow;

class SudokuFrame : public wxFrame {
private:
	SudokuWindow *mainwindow;
	HTPWindow *howtoplaywindow;
	CreditsWindow *creditswindow;
	BoardWindow *boardwindow;
	wxBoxSizer* boxSizer;
	void fitwindowSize();

public:
	SudokuFrame(const wxString &title);
	void InitComponents();
	void ShowMainWindow();
	void ShowBoardWindow();
	void ShowHTPWindow();
	void ShowCreditWindow();
};