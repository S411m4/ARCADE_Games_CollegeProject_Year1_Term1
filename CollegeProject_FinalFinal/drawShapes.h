#pragma once
#include "grid.h"

enum LineDir
{
	Horizontal, Vertical
};

void DrawLine(Grid *grid, int x, int y, int length, LineDir dir, char symbol)
{
	switch (dir)
	{
	case Horizontal:
		for (int l = 0; l < length; l++)
		{
			grid->DrawAtPixel(y, x+l, symbol);
		}
		break;

	case Vertical:
		for (int l = 0; l < length; l++)
		{
			grid->DrawAtPixel(y+l, x, symbol);
		}
		break;
	}
	
}