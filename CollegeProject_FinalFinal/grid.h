#pragma once

#include <vector>
#include <string>

class Grid
{
	public:
		Grid(unsigned int height, unsigned int width, unsigned int origin_x, unsigned int origin_y, char draw_symbol);
		void Draw();
		int GetGridWidth();
		int GetGridHeight();
		void DrawAtPixel(unsigned int x, unsigned int y, char draw_symbol);
		void DrawTextAt(unsigned int x, unsigned int y, std::string text);

	private:
		unsigned int height, width; 
		unsigned int origin_x, origin_y;
		char draw_symbol;
		std::vector<std::vector<char>> printable_grid;		 //0
};

