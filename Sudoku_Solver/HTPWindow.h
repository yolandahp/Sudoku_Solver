#pragma once
#include "wx\wx.h" 
#include "SudokuFrame.h"

class HTPWindow : public wxWindow
{
public:
	HTPWindow(SudokuFrame *parent);
	~HTPWindow();
	void OnPaint(wxPaintEvent &event);
	void BackToMainMenu(wxCommandEvent &event);

private:
	SudokuFrame *parent;

	wxBitmap *mainmenu = nullptr;
	wxBitmap *htpbg = nullptr;

	wxBitmapButton *back;

	void LoadBitmap();
	DECLARE_EVENT_TABLE()
};

