#include "BoardWindow.h"
#include "Cell.h"
#include <wx/stdpaths.h> 
#include <wx/filename.h> 
#include <wx/arrimpl.cpp>
#include <wx/dynarray.h>
#include <string.h>
using namespace std;

WX_DEFINE_ARRAY(Cell *, Objectarray);
BEGIN_EVENT_TABLE(BoardWindow, wxWindow)
	EVT_PAINT(BoardWindow::OnPaint)
	EVT_BUTTON(1001, BoardWindow::ClickSolve)
	EVT_BUTTON(1002, BoardWindow::ClickReset)
	EVT_BUTTON(4003, BoardWindow::BackToMainMenu)
	EVT_BUTTON(1010, BoardWindow::Response)
END_EVENT_TABLE()

Objectarray arr_obj;

BoardWindow::BoardWindow(SudokuFrame *parent) : wxWindow(parent, wxID_ANY) {
	this->SetBackgroundColour(wxColour(*wxWHITE));
	wxInitAllImageHandlers();
	wxImageHandler *jpgLoader = new wxJPEGHandler();
	wxImageHandler *pngLoader = new wxPNGHandler();
	wxImage::AddHandler(jpgLoader);
	wxImage::AddHandler(pngLoader);
	this->LoadMainBitmap();
	this->parent = parent;

	button1 = new wxBitmapButton(this, 1001, *solvebutton, wxPoint(597, 229.4), wxDefaultSize, wxBORDER_NONE);
	button2 = new wxBitmapButton(this, 1002, *resetbutton, wxPoint(600, 65), wxDefaultSize, wxBORDER_NONE);
	button3 = new wxBitmapButton(this, 4003, *mainbutton, wxPoint(598.9, 401.2), wxDefaultSize, wxBORDER_NONE);

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cell = new Cell(this, (80 + 50 * i), (78 + 50 * j), arr_obj.GetCount(), 0);
			cell->Bind(wxEVT_BUTTON, &BoardWindow::Response, this);
			arr_obj.Add(cell);
		}
	}
}

BoardWindow::~BoardWindow() {
	delete boardBitmap;
	delete solvebutton;
	delete resetbutton;
	delete mainbutton;
	delete button1;
	delete button2;
	delete button3;
	arr_obj.Clear();
}

void BoardWindow::OnPaint(wxPaintEvent &event) {
	wxPaintDC pdc1(this);
	if (boardBitmap != nullptr)
		pdc1.DrawBitmap(*boardBitmap, wxPoint(-10, 0), true);
}

void BoardWindow::Response(wxCommandEvent & event)
{
	wxMessageOutputDebug().Printf("hehe");

	Cell *temp = wxDynamicCast(event.GetEventObject(), Cell);

	wxMessageOutputDebug().Printf("%d %d", temp->GetX(), temp->GetY());
	wxMessageOutputDebug().Printf("%d", temp->GetIdx());
	int t = (temp->GetT() + 1) % 10;
	temp->SetT(t);
	temp->UpdateCell();
}

void BoardWindow::BackToMainMenu(wxCommandEvent & event)
{
	parent->ShowMainWindow();
}

bool BoardWindow::SolveSudoku(int grid[N][N])
{
	int status = 0;
	int arr[10];

	for (int i = 0; i < 9; i++) {
		memset(arr, 0, sizeof arr);
		for (int j = 0; j < 9; j++) {
			if (grid[i][j] != 0) {
				if(arr[grid[i][j]] == 0) arr[grid[i][j]] = 1;
				else return false;
			}
		}
	}

	for (int j = 0; j < 9; j++) {
		memset(arr, 0, sizeof arr);
		for (int i = 0; i < 9; i++) {
			if (grid[i][j] != 0) {
				if (arr[grid[i][j]] == 0) arr[grid[i][j]] = 1;
				else return false;
			}
		}
	}

	for (int k = 0; k < 3; k++) {
		for (int l = 0; l < 3; l++) {
			memset(arr, 0, sizeof(arr));
			for (int i = 0 + 3*k; i < 3 + 3*k; i++) {
				for (int j = 0 + 3*l; j < 3 + 3*l; j++) {
					if (grid[i][j] != 0) {
						if (arr[grid[i][j]] == 0) arr[grid[i][j]] = 1;
						else return false;
					}
				}
			}
		}
	}

	int row, col;
	if (!FindUnassignedLocation(grid, row, col))
		return true;

	for (int num = 1; num <= 9; num++) {
		if (isSafe(grid, row, col, num)) {
			grid[row][col] = num;

			if (SolveSudoku(grid))
				return true;
			grid[row][col] = UNASSIGNED;
		}
	}
	wxMessageOutputDebug().Printf("False");
	return false;
}

bool BoardWindow::FindUnassignedLocation(int grid[N][N], int & row, int & col)
{
	for (row = 0; row < N; row++)
		for (col = 0; col < N; col++)
			if (grid[row][col] == UNASSIGNED)
				return true;
	return false;
}

bool BoardWindow::UsedInRow(int grid[N][N], int row, int num)
{
	for (int col = 0; col < N; col++)
		if (grid[row][col] == num)
			return true;
	return false;
}

bool BoardWindow::UsedInCol(int grid[N][N], int col, int num)
{
	for (int row = 0; row < N; row++)
		if (grid[row][col] == num)
			return true;
	return false;
}

bool BoardWindow::UsedInBox(int grid[N][N], int boxStartRow, int boxStartCol, int num)
{
	for (int row = 0; row < 3; row++)
		for (int col = 0; col < 3; col++)
			if (grid[row + boxStartRow][col + boxStartCol] == num)
				return true;
	return false;
}

bool BoardWindow::isSafe(int grid[N][N], int row, int col, int num)
{
	return !UsedInRow(grid, row, num) && !UsedInCol(grid, col, num) && !UsedInBox(grid, row - row % 3, col - col % 3, num);
}

void BoardWindow::ClickSolve(wxCommandEvent & event) {
	int grid[9][9];
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			grid[j][i] = arr_obj[9 * i + j]->GetT();
		}
	}

	if (SolveSudoku(grid) == true) {
		wxMessageBox(wxT("We found a solution!"));
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				int t = grid[j][i];
				arr_obj[9 * i + j]->SetT(t);
				arr_obj[9 * i + j]->UpdateCell();
			}
		}
	}
	else {
		wxMessageBox(wxT("No solution exists!"));
		for (unsigned int i = 0; i < arr_obj.GetCount(); i++) {
			arr_obj[i]->SetT(0);
			arr_obj[i]->UpdateCell();
		}
	}
}

void BoardWindow::ClickReset(wxCommandEvent & event) {
	for (unsigned int i = 0; i < arr_obj.GetCount(); i++) {
		arr_obj[i]->SetT(0);
		arr_obj[i]->UpdateCell();
	}
	wxMessageBox(wxT("Board has been reset!"));
}

void BoardWindow::LoadMainBitmap() {
	wxStandardPaths &stdPaths = wxStandardPaths::Get();
	wxString fileLocation = stdPaths.GetExecutablePath();
	wxString fileLocation1 = wxFileName(fileLocation).GetPath() + wxT("\\solvethis.jpg");
	wxString fileLocation2 = wxFileName(fileLocation).GetPath() + wxT("\\reset.jpg");
	wxString fileLocation3 = wxFileName(fileLocation).GetPath() + wxT("\\boardpolosan.jpg");
	wxString fileLocation4 = wxFileName(fileLocation).GetPath() + wxT("\\0.jpg");
	wxString fileLocation5 = wxFileName(fileLocation).GetPath() + wxT("\\1.png");
	wxString fileLocation6 = wxFileName(fileLocation).GetPath() + wxT("\\2.png");
	wxString fileLocation7 = wxFileName(fileLocation).GetPath() + wxT("\\3.png");
	wxString fileLocation8 = wxFileName(fileLocation).GetPath() + wxT("\\4.png");
	wxString fileLocation9 = wxFileName(fileLocation).GetPath() + wxT("\\5.png");
	wxString fileLocation10 = wxFileName(fileLocation).GetPath() + wxT("\\6.png");
	wxString fileLocation11 = wxFileName(fileLocation).GetPath() + wxT("\\7.png");
	wxString fileLocation12 = wxFileName(fileLocation).GetPath() + wxT("\\8.png");
	wxString fileLocation13 = wxFileName(fileLocation).GetPath() + wxT("\\9.png");
	wxString fileLocation14 = wxFileName(fileLocation).GetPath() + wxT("\\mainmenu.jpg");

	wxImage image1(fileLocation1, wxBITMAP_TYPE_JPEG);
	wxImage image2(fileLocation2, wxBITMAP_TYPE_JPEG);
	wxImage image3(fileLocation3, wxBITMAP_TYPE_JPEG);
	wxImage image4(fileLocation4, wxBITMAP_TYPE_JPEG);
	wxImage image5(fileLocation5, wxBITMAP_TYPE_PNG);
	wxImage image6(fileLocation6, wxBITMAP_TYPE_PNG);
	wxImage image7(fileLocation7, wxBITMAP_TYPE_PNG);
	wxImage image8(fileLocation8, wxBITMAP_TYPE_PNG);
	wxImage image9(fileLocation9, wxBITMAP_TYPE_PNG);
	wxImage image10(fileLocation10, wxBITMAP_TYPE_PNG);
	wxImage image11(fileLocation11, wxBITMAP_TYPE_PNG);
	wxImage image12(fileLocation12, wxBITMAP_TYPE_PNG);
	wxImage image13(fileLocation13, wxBITMAP_TYPE_PNG);
	wxImage image14(fileLocation14, wxBITMAP_TYPE_JPEG);

	solvebutton = new wxBitmap(image1);
	resetbutton = new wxBitmap(image2);
	boardBitmap = new wxBitmap(image3);
	mainbutton = new wxBitmap(image14);
	cell0 = new wxBitmap(image4.Scale(45, 45));
	cell1 = new wxBitmap(image5.Scale(45, 45));
	cell2 = new wxBitmap(image6.Scale(45, 45));
	cell3 = new wxBitmap(image7.Scale(45, 45));
	cell4 = new wxBitmap(image8.Scale(45, 45));
	cell5 = new wxBitmap(image9.Scale(45, 45));
	cell6 = new wxBitmap(image10.Scale(45, 45));
	cell7 = new wxBitmap(image11.Scale(45, 45));
	cell8 = new wxBitmap(image12.Scale(45, 45));
	cell9 = new wxBitmap(image13.Scale(45, 45));
}

