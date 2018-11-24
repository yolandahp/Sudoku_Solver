#pragma once
#include "wx\wx.h" 
#include "SudokuFrame.h"

class CreditsWindow : public wxWindow
{
public:
	CreditsWindow(SudokuFrame *parent);
	~CreditsWindow();
	void OnPaint(wxPaintEvent &event);
	void BackToMainMenu(wxCommandEvent &event);

private:
	wxBitmap *mainmenu = nullptr;
	wxBitmap *creditbg = nullptr;

	wxBitmapButton *buttonmainmenu;

	SudokuFrame *parent;

	void LoadBitmap();
	DECLARE_EVENT_TABLE()

};

