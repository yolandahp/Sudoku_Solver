#include "wx\wx.h"
#include "SudokuFrame.h"
class MainApp : public wxApp {
public:
	virtual	bool OnInit();
};

IMPLEMENT_APP(MainApp)
DECLARE_APP(MainApp)

bool MainApp::OnInit() {
	SudokuFrame	*frame = new SudokuFrame(wxT("Sudoku Solver"));
	frame->Show(true);
	return true;
}