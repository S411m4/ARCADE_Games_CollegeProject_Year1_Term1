#pragma once
#include "grid.h"
#include "consoleutils.h"
#include "XOGameClass.h"
#include "SnakeGameClass.h"
#include "RacingGameClass.h"
#include <fstream>


class Menu
{
	public:
		Menu();
		~Menu();
		void TakeUserInput();

	private:
		void ChooseGame();
		void DrawArcade();
		void DrawTitles();
		void HighScoreScreen();

		void DrawXOTitle(Grid *pGrid,int &startX, int &startY);
		void DrawSnakeTitle(Grid *pGrid,int &startX, int &startY);
		void DrawRaceTitle(Grid *pGrid,int &startX, int &startY);

		Grid *pArcadeGrid;
		Grid* pTitlesGrid;
		Grid* pChosenGrid;
		Grid* pHighScoreGrid;
		Console *pConsole;

		unsigned int chosenGameIndex;
		unsigned int NoOfGames = 3;
		bool gameChosen = false;
		XOGame* xo;
		SnakeGame *snake;
		RacingGame *race;
		char currentGameLetter = ' ';
};

