#include "SudokuWindow.h"
#include <wx/stdpaths.h> 
#include <wx/filename.h> 

BEGIN_EVENT_TABLE(SudokuWindow, wxWindow)
	EVT_PAINT(SudokuWindow::OnPaint)
	EVT_BUTTON(1001, SudokuWindow::ClickPlay)
	EVT_BUTTON(1002, SudokuWindow::ClickHTP)
	EVT_BUTTON(1003, SudokuWindow::ClickCredit)
END_EVENT_TABLE()

SudokuWindow::SudokuWindow(SudokuFrame *parent) : wxWindow(parent, wxID_ANY) {
	this->SetBackgroundColour(wxColour(*wxBLACK));
	wxInitAllImageHandlers();
	wxImageHandler *pngLoader = new wxPNGHandler();
	wxImage::AddHandler(pngLoader);
	wxImageHandler *jpgLoader = new wxJPEGHandler();
	wxImage::AddHandler(jpgLoader);
	this->LoadMainBitmap();
	this->parent = parent;
}

SudokuWindow::~SudokuWindow()
{
	delete playbutton;
	delete htpbutton;
	delete creditbutton;
	delete sudokubg;

	delete button1;
	delete button2;
	delete button3;
}

void SudokuWindow::OnPaint(wxPaintEvent & event)
{
	wxPaintDC pdc(this);
	pdc.DrawBitmap(*sudokubg, wxPoint(-10, 0), true);

	button1 = new wxBitmapButton(this, 1001, *playbutton, wxPoint(300, 348), wxDefaultSize, wxBORDER_NONE);
	button2 = new wxBitmapButton(this, 1002, *htpbutton, wxPoint(105, 350), wxDefaultSize, wxBORDER_NONE);
	button3 = new wxBitmapButton(this, 1003, *creditbutton, wxPoint(452, 389.5), wxDefaultSize, wxBORDER_NONE);
}

void SudokuWindow::ClickPlay(wxCommandEvent & event)
{
	parent->ShowBoardWindow();
}

void SudokuWindow::ClickHTP(wxCommandEvent & event)
{
	parent->ShowHTPWindow();
}

void SudokuWindow::ClickCredit(wxCommandEvent & event)
{
	parent->ShowCreditWindow();
}

void SudokuWindow::LoadMainBitmap()
{
	wxStandardPaths &stdPaths = wxStandardPaths::Get();
	wxString fileLocation = stdPaths.GetExecutablePath();

	wxString fileLocation1 = wxFileName(fileLocation).GetPath() + wxT("\\start.jpg");
	wxString fileLocation2 = wxFileName(fileLocation).GetPath() + wxT("\\howtouse.jpg");
	wxString fileLocation3 = wxFileName(fileLocation).GetPath() + wxT("\\credits.jpg");
	wxString fileLocation4 = wxFileName(fileLocation).GetPath() + wxT("\\mainmenupolos.png");

	wxImage image1(fileLocation1, wxBITMAP_TYPE_JPEG);
	wxImage image2(fileLocation2, wxBITMAP_TYPE_JPEG);
	wxImage image3(fileLocation3, wxBITMAP_TYPE_JPEG);
	wxImage image4(fileLocation4, wxBITMAP_TYPE_PNG);

	playbutton = new wxBitmap(image1);
	htpbutton = new wxBitmap(image2);
	creditbutton = new wxBitmap(image3);
	sudokubg = new wxBitmap(image4);
}

