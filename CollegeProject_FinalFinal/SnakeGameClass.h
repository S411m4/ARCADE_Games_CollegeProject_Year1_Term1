#pragma once
#include "grid.h"
#include "consoleutils.h"

class SnakeGame
{
	public:
		SnakeGame();
		~SnakeGame();
		void GameLoop();
		void InitalizeGame();

	private:
		void Draw();
		void Input();
		void GameAlgorithm();

		Grid *pGrid;
		Console *pConsole;

		bool gameOver;
		const unsigned int width = 20;
		const unsigned int height = 10;

		unsigned int x, y, fruitX, fruitY, score;
		unsigned int tailX[100], tailY[100];
		unsigned int nTail;
		enum eDirection{STOP = 0, LEFT, RIGHT, UP, DOWN};
		eDirection dir;
		
};

