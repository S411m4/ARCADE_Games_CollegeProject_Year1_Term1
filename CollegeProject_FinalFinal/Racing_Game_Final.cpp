// Racing_Game_Final.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include<stdlib.h>
#include<Windows.h>
#include<time.h>
#include<string>
// for console input/output "like keyboard controller"
#include<conio.h>
using namespace std;

bool exitGame;
bool gameOver;
bool isMoving;
bool bombExplode;
bool dead;

int iwidth;
int iheight;
int ispeed;
int ilife = 5;
int iscore;
int imyCarX, imyCarY;
int ihighScore;
int ihighestScore[5];
int ienemyX[4];
int ienemyY[4] = { -8,-18,-28,-38 };
int ienemyPositonX, ienemyPositonY;
int enemyNum;

string bombParticle1[4] = { "o   o"," ooo "," ooo ","o   o" };
string bombParticle2[4] = { " ooo ","o   o","o   o"," ooo " };

//Drawing the car
/* 
   #
* # #
*  #
* # #
*/
string myCar[4] = { " # ","# #"," # ","# #" };

void gotoxy(int x, int y) {
	//Defines the coordinates of a character cell in a console screen buffer.
	//The origin of the coordinate system (0,0) is at the top.

	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void hideCursor() {
	CONSOLE_CURSOR_INFO cursor;
	cursor.dwSize = 100;
	cursor.bVisible = false;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}

void startUp() {
	srand(time(NULL));
	 exitGame = false;
	 gameOver = false;
	 isMoving = false;
	 dead = false;
	 iwidth = 19;
	 iheight = 20;
	 ispeed = 1;
	 iscore = 0;
	 imyCarX = 8;
	 imyCarY = 16;
	 enemyNum = 4;
	 //not understanded
	 for (int i = 0; i < enemyNum; i++)
	 {
		 ienemyPositonX = rand() % 3;

		 if (ienemyPositonX == 0)
			 ienemyX[i] == 2;
		 else if (ienemyPositonX == 1)
			 ienemyX[i] == 8;
		 else if (ienemyPositonX == 2)
			 ienemyX[i] == 14;
	 }
}

void layout() {
	for (int i = 0; i < iheight; i++) {
		gotoxy(0, i);
		cout << "#                   #";
		if (i % 2 == 0 && isMoving) {
			gotoxy(6, i);
			cout << "|     |";
		}
		else if (i % 2 != 0 && !isMoving) {
			gotoxy(6, i);
			cout << "|     |";
		}
	}
	gotoxy(5, 21);
	cout << "life : " << ilife;
	gotoxy(5, 22);
	cout << "score : " << iscore;
}

void drawMyCar() {
	if (!dead) {
		for (int i = 0; i < 4; i++) {
			gotoxy(imyCarX, imyCarY + i);
			cout << myCar[i];
		}
	}
	else {
		for (int i = 0; i < 4; i++) {
			gotoxy(imyCarX, imyCarY + i);
			cout << "    ";
		}
	}
}
void drawEnemyCar()
{
	//ienemyY[4] = { -8,-18,-28,-38 };

	for (int i = 0; i < enemyNum; i++) 
	{
		if (ienemyY[i] + 3 > 0)
		{
			gotoxy(ienemyX[i], ienemyY[i] + 3);
			cout << " # ";
		}
		if (ienemyY[i] + 2 > 0)
		{
			gotoxy(ienemyX[i], ienemyY[i] + 2);
			cout << "# #";
		}
		if (ienemyY[i] + 1 > 0)
		{
			gotoxy(ienemyX[i], ienemyY[i] + 1);
			cout << " # ";
		}
		if (ienemyY[i] > 0)
		{
			gotoxy(ienemyX[i], ienemyY[i]);
			cout << "# #";
		}
		if (ienemyY[i] + 3 >= 20)
		{
			gotoxy(ienemyX[i], ienemyY[i] + 3);
			cout << "   ";
		}
		if (ienemyY[i] + 2 >= 20)
		{
			gotoxy(ienemyX[i], ienemyY[i] + 2);
			cout << "   ";
		}
		if (ienemyY[i] + 1 >= 20)
		{
			gotoxy(ienemyX[i], ienemyY[i] + 1);
			cout << "   ";
		}
		if (ienemyY[i] >= 20)
		{
			gotoxy(ienemyX[i], ienemyY[i]);
			cout << "   ";
		}
	}
}
int main()
{
	
	return 0;
}