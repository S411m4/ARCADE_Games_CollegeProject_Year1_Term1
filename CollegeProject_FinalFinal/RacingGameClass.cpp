#include "RacingGameClass.h"
#include <fstream>

void RacingGame::gotoxy(int x, int y)
{
	COORD coord{};
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void RacingGame::hideCursor()
{
	CONSOLE_CURSOR_INFO cursor{};
	cursor.dwSize = 100;
	cursor.bVisible = false;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}

void RacingGame::InitalizeGame()
{
	hideCursor();
	startUp();
	splashScreen();
	spiralEffect();
	transition();
	game();
}

void RacingGame::GameLoop()
{
	while (!gameOver) {
		layout();
		input();
		mecha();
		drawMyCar();
		drawEnemyCar();

		if (dead)
		{
			died();
			game_Over();
			Sleep(500);
		}
		Sleep(50);
	}
}

void RacingGame::startUp()
{
	
	srand(time(NULL));
	exitGame = false;
	gameOver = false;
	isMoving = false;
	dead = false;
	height = 20;
	width = 19;
	myCarX = 8;
	myCarY = 16;
	speed = 1;
	enemyNum = 4;
	score = 0;

	for (int i = 0; i < enemyNum; i++)
	{
		enemyPositionX = rand() % 3;
		if (enemyPositionX == 0) enemyX[i] = 2;
		else if (enemyPositionX == 1) enemyX[i] = 8;
		else if (enemyPositionX == 2) enemyX[i] = 14;
	}

	enemyY[0] = -8;
	enemyY[1] = -18;
	enemyY[2] = -28;
	enemyY[3] = -38;
}

void RacingGame::layout() {
	for (int i = 0; i < height; i++) {
		gotoxy(0, i);
		std::cout << "#                   #";
		if (i % 2 == 0 && isMoving) {
			gotoxy(6, i);
			std::cout << "|      |";
		}
		else if (i % 2 == 0 && !isMoving) {
			gotoxy(6, i);
			std::cout << "|      |";
		}
	}
	//gotoxy(5, 21);
	//std::cout << "Life : " << life;
	gotoxy(5, 21);
	std::cout << "Score: " << score;
}

void RacingGame::drawMyCar() {
	if (!dead) {
		for (int i = 0; i < 4; i++) {
			gotoxy(myCarX, myCarY + i);
			std::cout << myCar[i];
		}
	}
	else {
		for (int i = 0; i < 4; i++) {
			gotoxy(myCarX, myCarY + i);
			std::cout << "   ";
		}
	}
}

void RacingGame::drawEnemyCar() {
	for (int i = 0; i < enemyNum; i++) {
		if (enemyY[i] + 3 > 0) {
			gotoxy(enemyX[i], enemyY[i] + 3);
			std::cout << " # ";
		}
		if (enemyY[i] + 2 > 0) {
			gotoxy(enemyX[i], enemyY[i] + 2);
			std::cout << "# #";
		}
		if (enemyY[i] + 1 > 0) {
			gotoxy(enemyX[i], enemyY[i] + 1);
			std::cout << " # ";
		}
		if (enemyY[i] > 0) {
			gotoxy(enemyX[i], enemyY[i]);
			std::cout << "# #";
		}
		if (enemyY[i] + 3 >= 20) {
			gotoxy(enemyX[i], enemyY[i] + 3);
			std::cout << "   ";
		}
		if (enemyY[i] + 2 >= 20) {
			gotoxy(enemyX[i], enemyY[i] + 2);
			std::cout << "   ";
		}
		if (enemyY[i] + 1 >= 20) {
			gotoxy(enemyX[i], enemyY[i] + 1);
			std::cout << "   ";
		}
		if (enemyY[i] >= 20) {
			gotoxy(enemyX[i], enemyY[i]);
			std::cout << "   ";
		}
	}
}

void RacingGame::input() {
	if (_kbhit()) {
		switch (_getch()) {
		case 72:
			if (myCarY > 0 && !dead) myCarY -= speed;
			break;
		case 75:
			if (myCarX > 2 && !dead) myCarX -= 6;
			break;
		case 77:
			if (myCarX < 14 && !dead) myCarX += 6;
			break;
		case 80:
			if (myCarY < 16 && !dead) myCarY += speed;
			break;
		}
	}
}

void RacingGame::mecha() {
	srand(time(NULL));
	if (isMoving)  isMoving = false;
	else isMoving = true;

	////reset enemy Y position to keep enemy cars moving
	for (int i = 0; i < enemyNum; i++)
	{
		if (enemyY[i] > 20)
		{
			enemyY[i] = -40;
		}
	}

	for (int i = 0; i < enemyNum; i++) {
		if (enemyY[i] < 21) { //
			enemyPositionX = rand() % 3;
			if (enemyPositionX == 0)  enemyX[i] = 2;
			else if (enemyPositionX == 1)  enemyX[i] = 8;
			else if (enemyPositionX == 2)  enemyX[i] = 14;
			enemyY[i] += 1;
			score++;
		}
	}

	//check car collision
	// 
	for (int i = 0; i < enemyNum; i++) {
		if ((myCarY <= enemyY[i] + 3 && myCarY >= enemyY[i] && myCarX == enemyX[i]) || (enemyY[i] >= myCarY && enemyY[i] <= myCarY + 3 && myCarX == enemyX[i] && myCarX == enemyX[i]))
			dead = true;
	}
}

void RacingGame::bombExplosion() {
	if (bombExplode) {
		for (int i = 0; i < 4; i++) {
			gotoxy(myCarX - 1, myCarY - 1 + i);
			std::cout << bombParticle1[i] << std::endl;
		}
		bombExplode = false;
	}
	else {
		for (int i = 0; i < 4; i++) {
			gotoxy(myCarX - 1, myCarY - 1 + i);
			std::cout << bombParticle2[i] << std::endl;
		}
		bombExplode = true;
	}
	Sleep(100);
}

void RacingGame::died() {
	if (dead) {
		//life--;
		//int count = 0;
		/*while (count != 10) {
			input();*/
			bombExplosion();
			gotoxy(2, 22);
			std::cout << "You got " << score << " Score!";
			//count++;
		//}
		/*gotoxy(2, 22);
		std::cout << "                    ";
		highestScore[life] = score;
		InitalizeGame();*/
	}
}
void RacingGame::transition() {
	for (int i = 19; i >= 0; i--) {
		gotoxy(1, i);
		std::cout << "#################";
		Sleep(15);
	}
	for (int i = 1; i < 20; i++) {
		gotoxy(1, i);
		std::cout << "                 ";
		Sleep(15);
	}
}
void RacingGame::game_Over() {
	/*for (int i = 0; i < life; i++) {
		if (highestScore[i] >= highestScore[i - 1]) highScore = highestScore[i];
		else if (highestScore[i] <= highestScore[i - 1]) highScore = highestScore[i - 1];
	}*/
	//if(dead)
	//{
	//if (life == 0) {
		gameOver = true;
	//	do {
			gotoxy(0, 0); std::cout << "###################";
			gotoxy(0, 1); std::cout << "#                 #";
			gotoxy(0, 2); std::cout << "#                 #";
			gotoxy(0, 3); std::cout << "#                 #";
			gotoxy(0, 4); std::cout << "#                 #";
			gotoxy(0, 5); std::cout << "#                 #";
			gotoxy(0, 6); std::cout << "#   GAME OVER!!   #";
			gotoxy(0, 7); std::cout << "#                 #";
			gotoxy(0, 8); std::cout << "#    HIGHSCORE    #";
			gotoxy(0, 9); std::cout << "#                 #";
			gotoxy(0, 10); std::cout << "#      " << score << "          #";
			gotoxy(0, 11); std::cout << "#                 #";
			gotoxy(0, 12); std::cout << "#                 #";
			gotoxy(0, 13); std::cout << "#                 #";
			gotoxy(0, 14); std::cout << "#                 #";
			gotoxy(0, 15); std::cout << "#                 #";
			gotoxy(0, 15); std::cout << "#                 #";
			gotoxy(0, 15); std::cout << "#                 #";
			//gotoxy(0, 16); std::cout << "#    PRESS  'X'   #";
			//gotoxy(0, 17); std::cout << "#     TO EXIT     #";
			gotoxy(0, 18); std::cout << "#                 #";
			gotoxy(0, 19); std::cout << "###################";
			gotoxy(0, 20); std::cout << "                   ";
			gotoxy(0, 21); std::cout << "                   ";
		//} while (_getch() != 'x');
	//}

			std::fstream raceScore("raceScore.txt", std::ios::out | std::ios::app);
			if (raceScore.is_open())
			{
				raceScore << score << "\n";
			}
			raceScore.close();
}

void RacingGame::spiralEffect() {
	int row = 1, col = 1;
	int last_row = height - 2, last_col = width - 2;
	while (row <= last_row && col <= last_col) {
		for (int i = col; i <= last_col; i++) {
			gotoxy(i, row);
			std::cout << "#";
			Sleep(2);
		}row++;
		for (int i = row; i <= last_row; i++) {
			gotoxy(last_col, i);
			std::cout << "#";
		}last_col--;
		if (row <= last_row) {
			for (int i = last_col; i >= col; i--) {
				gotoxy(i, last_row);
				std::cout << "#";
				Sleep(1);
			}last_row--;
		}
		if (col <= last_col) {
			for (int i = last_row; i >= row; i--) {
				gotoxy(col, i);
				std::cout << "#";
			}col++;
		}
	}
	row = 1, col = 1;
	last_row = height - 2, last_col = width - 3;
	while (row <= last_row && col <= last_col) {
		for (int i = col; i <= last_col; i++) {
			gotoxy(i, row);
			std::cout << " ";
			Sleep(2);
		}row++;
		for (int i = row; i <= last_row; i++) {
			gotoxy(last_col, i);
			std::cout << "  ";
		}last_col--;
		if (row <= last_row) {
			for (int i = last_col; i >= col; i--) {
				gotoxy(i, last_row);
				std::cout << " ";
				Sleep(1);
			}last_row--;
		}
		if (col <= last_col) {
			for (int i = last_row; i >= row; i--) {
				gotoxy(col, i);
				std::cout << " ";
			}col++;
		}
	}
}
void RacingGame::splashScreen() {
	gotoxy(0, 0); std::cout << "###################";
	gotoxy(0, 1); std::cout << "#                 # ";
	gotoxy(0, 2); std::cout << "#        #        #  ";
	gotoxy(0, 3); std::cout << "#       ##        #  ";
	gotoxy(0, 4); std::cout << "#        #        #  ";
	gotoxy(0, 5); std::cout << "#        #        #  ";
	gotoxy(0, 6); std::cout << "#       ###       #  ";
	gotoxy(0, 7); std::cout << "#                 #  ";
	gotoxy(0, 8); std::cout << "#     #  #  #     #  ";
	gotoxy(0, 9); std::cout << "#     #  ## #     #  ";
	gotoxy(0, 10); std::cout << "#     #  # ##     #  ";
	gotoxy(0, 11); std::cout << "#     #  #  #     #  ";
	gotoxy(0, 12); std::cout << "#                 #  ";
	gotoxy(0, 13); std::cout << "#        #        #  ";
	gotoxy(0, 14); std::cout << "#       ##        #  ";
	gotoxy(0, 15); std::cout << "#        #        #  ";
	gotoxy(0, 16); std::cout << "#        #        #  ";
	gotoxy(0, 17); std::cout << "#       ###       #  ";
	gotoxy(0, 18); std::cout << "#                 #  ";
	gotoxy(0, 19); std::cout << "###################  ";
	Sleep(500);
}

void RacingGame::game() {
	do {
		gotoxy(0, 0); std::cout << "###################";
		gotoxy(0, 1); std::cout << "#                 #";
		gotoxy(0, 2); std::cout << "#   BRICK  GAME   #";
		gotoxy(0, 3); std::cout << "#                 #";
		gotoxy(0, 4); std::cout << "#    RACE  CAR    #";
		gotoxy(0, 5); std::cout << "#                 #";
		gotoxy(0, 6); std::cout << "#                 #";
		gotoxy(0, 7); std::cout << "#    #   |   #    #";
		gotoxy(0, 8); std::cout << "#    #       #    #";
		gotoxy(0, 9); std::cout << "#    #   |   #    #";
		gotoxy(0, 10); std::cout << "#    #       #    #";
		gotoxy(0, 11); std::cout << "#    #   |   #    #";
		gotoxy(0, 12); std::cout << "#    #       #    #";
		gotoxy(0, 13); std::cout << "#    #   |   #    #";
		gotoxy(0, 14); std::cout << "#                 #";
		gotoxy(0, 15); std::cout << "#                 #";
		gotoxy(0, 16); std::cout << "#  PRESS 'Space'  #";
		gotoxy(0, 17); std::cout << "#    TO START     #";
		gotoxy(0, 18); std::cout << "#                 #";
		gotoxy(0, 19); std::cout << "###################";
	} while (_getch() != 32);
}