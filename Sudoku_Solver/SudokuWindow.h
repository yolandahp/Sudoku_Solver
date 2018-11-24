#pragma once
#include "wx\wx.h"
#include "SudokuFrame.h"

class SudokuWindow : public wxWindow {
public:
	SudokuWindow(SudokuFrame *parent);
	~SudokuWindow();
	void OnPaint(wxPaintEvent &event);
	
	void ClickPlay(wxCommandEvent &event);
	void ClickHTP(wxCommandEvent &event);
	void ClickCredit(wxCommandEvent &event);

private:
	wxBitmap *playbutton = nullptr;
	wxBitmap *htpbutton = nullptr;
	wxBitmap *creditbutton = nullptr;
	wxBitmap *sudokubg = nullptr;

	wxBitmapButton *button1;
	wxBitmapButton *button2;
	wxBitmapButton *button3;

	SudokuFrame *parent;

	void LoadMainBitmap();
	DECLARE_EVENT_TABLE()
};