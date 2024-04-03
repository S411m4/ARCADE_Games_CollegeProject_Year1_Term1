#pragma once
#include "GameMath.h"
#include <vector>
#include "grid.h"
#include "consoleutils.h"

struct Snake
{
	Vector2 head;
	std::vector<Vector2> bodyParts;

};

class SnakeGame
{
	public:
		SnakeGame();
		~SnakeGame();

		void GameLoop();

		void MoveSnake();
		bool IsCollidedBorder();
		bool IsGameOver();
		bool IsCollidedItself();
		void Apple();
		bool IsCollidedApple();
		void GrowSnake();


	private:	
		void DrawSnakeGrid();
		void InitalizeSnake();

		Grid *pgrid;
		Console *pconsole;
		Snake snake;
		Vector2 applePos;
		bool gameOver = false;
		
};

