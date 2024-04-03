#pragma once
#include "consoleutils.h"
#include "grid.h"
#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>


class RacingGame
{
	public:
		RacingGame() = default;
		~RacingGame() = default;
		void InitalizeGame(); 
		void GameLoop();

	private:
		void startUp();
		void gotoxy(int x, int y);
		void layout();
		void drawMyCar();
		void drawEnemyCar();
		void input();
		void mecha();
		void bombExplosion();
		void died();
		void transition();
		void game_Over();
		void spiralEffect();
		void splashScreen();
		void hideCursor();
		void game();
		
		

		bool exitGame, gameOver, isMoving, bombExplode, dead;
		int height, width, speed, score, myCarX, myCarY, highScore, enemyNum, enemyPositionX, enemyPositionY;
		//int life = 5;
		int enemyX[4];
		int enemyY[4] = { -8,-18,-28,-38 };
		std::string bombParticle1[4] = { "o   o"," ooo "," ooo ","o   o" };
		std::string bombParticle2[4] = { " ooo ","o   o","o   o"," ooo " };
		std::string myCar[4] = { " # ","# #"," # ","# #" };

};

