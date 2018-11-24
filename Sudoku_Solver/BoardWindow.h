#pragma once
#include "wx\wx.h" 
#include "SudokuFrame.h"
#include <wx/app.h>
#include <wx/arrimpl.cpp>
#include <wx/dynarray.h>
#include <wx/dcbuffer.h>

#define UNASSIGNED 0
#define N 9

class Cell;

class BoardWindow : public wxWindow {
public:
	BoardWindow(SudokuFrame *parent);
	~BoardWindow();
	void OnPaint(wxPaintEvent &event);
	void ClickSolve(wxCommandEvent &event);
	void ClickReset(wxCommandEvent &event);
	void Response(wxCommandEvent &event);
	void BackToMainMenu(wxCommandEvent &event);
	bool SolveSudoku(int grid[N][N]);
	bool FindUnassignedLocation(int grid[N][N], int &row, int &col);
	bool UsedInRow(int grid[N][N], int row, int num);
	bool UsedInCol(int grid[N][N], int col, int num);
	bool UsedInBox(int grid[N][N], int boxStartRow, int boxStartCol, int num);
	bool isSafe(int grid[N][N], int row, int col, int num);

	Cell *cell;
	wxBitmap *cell0 = nullptr;
	wxBitmap *cell1 = nullptr;
	wxBitmap *cell2 = nullptr;
	wxBitmap *cell3 = nullptr;
	wxBitmap *cell4 = nullptr;
	wxBitmap *cell5 = nullptr;
	wxBitmap *cell6 = nullptr;
	wxBitmap *cell7 = nullptr;
	wxBitmap *cell8 = nullptr;
	wxBitmap *cell9 = nullptr;

private:
	wxBitmap *boardBitmap = nullptr;
	wxBitmap *solvebutton = nullptr;
	wxBitmap *resetbutton = nullptr;
	wxBitmap *mainbutton = nullptr;

	wxBitmapButton *button1;
	wxBitmapButton *button2;
	wxBitmapButton *button3;

	void LoadMainBitmap();

	SudokuFrame *parent;
	DECLARE_EVENT_TABLE()
};

