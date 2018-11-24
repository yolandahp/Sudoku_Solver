#include "CreditsWindow.h"
#include <wx/stdpaths.h> 
#include <wx/filename.h>

BEGIN_EVENT_TABLE(CreditsWindow, wxWindow)
	EVT_PAINT(CreditsWindow::OnPaint)
	EVT_BUTTON(1031, CreditsWindow::BackToMainMenu)
END_EVENT_TABLE()


CreditsWindow::CreditsWindow(SudokuFrame *parent) : wxWindow(parent, wxID_ANY)
{
	this->SetBackgroundColour(wxColour(*wxBLACK));
	wxInitAllImageHandlers();
	wxImageHandler *pngLoader = new wxPNGHandler();
	wxImage::AddHandler(pngLoader);
	this->parent = parent;
	this->LoadBitmap();

	buttonmainmenu = new wxBitmapButton(this, 1031, *mainmenu, wxPoint(670, 479), wxDefaultSize, wxBORDER_NONE);
}


CreditsWindow::~CreditsWindow()
{
	delete mainmenu;
	delete buttonmainmenu;
}

void CreditsWindow::OnPaint(wxPaintEvent &event) {
	wxPaintDC pdc1(this);
	if (creditbg != nullptr)
		pdc1.DrawBitmap(*creditbg, wxPoint(-10, 0), true);
}

void CreditsWindow::BackToMainMenu(wxCommandEvent & event)
{
	parent->ShowMainWindow();
}

void CreditsWindow::LoadBitmap()
{
	wxStandardPaths &stdPaths = wxStandardPaths::Get();
	wxString fileLocation = stdPaths.GetExecutablePath();

	wxString fileLocation1 = wxFileName(fileLocation).GetPath() + wxT("\\mainmenucredits.jpg");
	wxString fileLocation2 = wxFileName(fileLocation).GetPath() + wxT("\\creditss.png");
	
	wxImage image1(fileLocation1, wxBITMAP_TYPE_JPEG);
	wxImage image2(fileLocation2, wxBITMAP_TYPE_PNG);
	
	mainmenu = new wxBitmap(image1);
	creditbg = new wxBitmap(image2);
}
