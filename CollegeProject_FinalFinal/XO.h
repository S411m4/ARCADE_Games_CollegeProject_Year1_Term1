#pragma once
#include "grid.h"
#include "consoleutils.h"

class XO
{
	public:
		XO();
		~XO();
		void GameLoop();
		void DrawAtCell(char symbol, int cell);
		unsigned int TakePlayerInput();
		void NextTurn();
		bool IsAllCellsFull();
		int CheckWinDraw(); 

	private:
		void DrawXOGrid();
		Grid *pgrid;
		Console *pconsole;
		char XO_values[9] = {
							'1','2','3',
							'4','5','6',
							'7','8','9' };

		char player_symbol = 'X';
		bool isGameOver = false;
		int state;
};

