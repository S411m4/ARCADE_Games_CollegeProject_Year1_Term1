#pragma once
#include "grid.h"
#include "consoleutils.h"

class XOGame
{
	public:
		XOGame();
		~XOGame();
		void IntializeGame();
		void GameLoop();

	private:
		void ResetGame();
		void DrawAtCell(char symbol, int cell);
		unsigned int TakePlayerInput();
		void NextTurn();
		bool IsAllCellsFull();
		int CheckWinDraw();


		Grid *pGrid;
		Console *pConsole;
		char XO_values[9] = { '1','2','3','4','5','6','7','8','9' };
		bool isGameOver = false;
		char player_symbol = 'X';
		int state;
		int xScore = 0, oScore = 0, dScore = 0;
};

