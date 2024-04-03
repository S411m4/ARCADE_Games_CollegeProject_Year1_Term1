#include "grid.h"
#include <iostream>
#include <vector>




Grid::Grid(unsigned int h, unsigned int w, unsigned int x, unsigned int y, char s)
	: height(h), width(w), origin_x(x), origin_y(y), draw_symbol(s)
{
	if (height < 3) { height = 3; }
	if (width < 3) { width = 3; }
	if (origin_x < 0) { origin_x = 0; }
	if (origin_y < 0) { origin_y = 0; }

	printable_grid.resize(height, std::vector<char>(width, draw_symbol));
}

void Grid::Draw()
{
	//case 1:
	// i -> row
	// j -> col
	
	//0000000000
	//0000000000
	//0000000000
	//0000000000
	//0000000000


	for (int y = 0; y < origin_y; y++)
	{
		std::cout << '\n';
	}

	for (int i = 0; i < height; i++)
	{
		for (int x = 0; x < origin_x; x++)
		{
			std::cout << ' ';
		}
		for (int j = 0; j < width; j++)
		{
			std::cout << printable_grid[i][j];
		}
		std::cout << '\n';
	}
}

int Grid::GetGridHeight() { return height; }
int Grid::GetGridWidth() { return width; }

void Grid::DrawAtPixel(unsigned int x, unsigned int y, char draw_symbol)
{
	if (x < 0 || x > height-1) { x = 0; }
	if (x < 0 || y > width-1) { y = 0; }

	printable_grid[x][y] = draw_symbol;

}

void Grid::DrawTextAt(unsigned int x, unsigned int y, std::string text)
{
	for (int i = 0; i < text.length(); i++)
	{
		DrawAtPixel( y , x + i, text[i]);
	}
}