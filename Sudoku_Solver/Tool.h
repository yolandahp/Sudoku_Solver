#pragma once
#include "wx\event.h"

class DrawingCanvas;

class Tool {
public:
	Tool();
	~Tool();
	void SetActiveCanvas(DrawingCanvas* canvas);
	virtual void ToolMouseLeftDown(wxMouseEvent &event) = 0;
	virtual void ToolMouseLeftUp(wxMouseEvent &event) = 0;
	virtual void ToolMouseMotion(wxMouseEvent &event) = 0;
protected:
	DrawingCanvas* activeCanvas;
};