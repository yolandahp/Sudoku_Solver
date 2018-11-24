#include "HTPWindow.h"
#include <wx/stdpaths.h> 
#include <wx/filename.h> 

BEGIN_EVENT_TABLE(HTPWindow, wxWindow)
	EVT_PAINT(HTPWindow::OnPaint)
	EVT_BUTTON(3001, HTPWindow::BackToMainMenu)
END_EVENT_TABLE()

HTPWindow::HTPWindow(SudokuFrame *parent) : wxWindow(parent, wxID_ANY)
{
	this->SetBackgroundColour(wxColour(*wxBLACK));
	this->parent = parent;
	this->LoadBitmap();

	back = new wxBitmapButton(this, 3001, *mainmenu, wxPoint(576.95, 462), wxDefaultSize, wxBORDER_NONE);
}


HTPWindow::~HTPWindow()
{
	delete back;
	delete mainmenu;
	delete htpbg;
}

void HTPWindow::BackToMainMenu(wxCommandEvent & event)
{
	parent->ShowMainWindow();
}

void HTPWindow::OnPaint(wxPaintEvent &event) {
	wxPaintDC pdc1(this);
	if (htpbg != nullptr)
		pdc1.DrawBitmap(*htpbg, wxPoint(-10, 0), true);
}

void HTPWindow::LoadBitmap()
{
	wxStandardPaths &stdPaths = wxStandardPaths::Get();
	wxString fileLocation = stdPaths.GetExecutablePath();
	wxString fileLocation1 = wxFileName(fileLocation).GetPath() + wxT("\\mainmenuhtp.jpg");
	wxString fileLocation2 = wxFileName(fileLocation).GetPath() + wxT("\\howtouse.png");

	wxImage image1(fileLocation1, wxBITMAP_TYPE_JPEG);
	wxImage image2(fileLocation2, wxBITMAP_TYPE_PNG);

	mainmenu = new wxBitmap(image1);
	htpbg = new wxBitmap(image2);
}
