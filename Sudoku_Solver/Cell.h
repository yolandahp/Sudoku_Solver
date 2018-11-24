#pragma once
#include <wx\wx.h>
#include "BoardWindow.h"

class Cell : public wxBitmapButton
{
public:
	Cell();
	Cell(BoardWindow * window, int koorx, int koory, int idx, int t);
	~Cell();
	void SetX(int posx);
	void SetY(int posy);
	void SetT(int tp);
	int GetX();
	int GetY();
	int GetT();
	int GetIdx();
	void UpdateCell();
private:
	int idx;
	int x;
	int y;
	int t;
	BoardWindow *parent;
};

