#include "Cell.h"
#include <wx/stdpaths.h> 
#include <wx/filename.h> 

Cell::Cell(){
}

Cell::Cell(BoardWindow * window, int koorx, int koory, int idx, int t) {
	this->parent = window;
	this->x = koorx;
	this->y = koory;
	this->idx = idx;
	this->t = t;

	Create(parent, wxID_ANY, *parent->cell0, wxPoint(this->x, this->y), wxDefaultSize, wxBORDER_NONE);
}


Cell::~Cell(){
}

void Cell::SetX(int posx){
	this->x = posx;
}

void Cell::SetY(int posy){
	this->y = posy;
}

void Cell::SetT(int tp){
	this->t = tp;
}

int Cell::GetX(){
	return this->x;
}

int Cell::GetY(){
	return this->y;
}

int Cell::GetT(){
	return this->t;
}

int Cell::GetIdx()
{
	return this->idx;
}

void Cell::UpdateCell()
{
	if(this->t == 0) this->SetBitmap(*parent->cell0);
	else if (this->t == 1) this->SetBitmap(*parent->cell1);
	else if (this->t == 2) this->SetBitmap(*parent->cell2);
	else if (this->t == 3) this->SetBitmap(*parent->cell3);
	else if (this->t == 4) this->SetBitmap(*parent->cell4);
	else if (this->t == 5) this->SetBitmap(*parent->cell5);
	else if (this->t == 6) this->SetBitmap(*parent->cell6);
	else if (this->t == 7) this->SetBitmap(*parent->cell7);
	else if (this->t == 8) this->SetBitmap(*parent->cell8);
	else if (this->t == 9) this->SetBitmap(*parent->cell9);
}
