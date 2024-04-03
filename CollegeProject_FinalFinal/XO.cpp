#include "XO.h"
#include <iostream>

XO::XO()
{
	pgrid = new Grid(7, 7, 20, 10, ' ');
	pconsole = new Console();

	DrawXOGrid();

	pgrid->Draw();
}

XO::~XO()
{
	delete pgrid;
	delete pconsole;	
}

void XO::DrawXOGrid()
{

	for (int i = 0; i < pgrid->GetGridHeight(); i += 2)
	{
		for (int j = 0; j < pgrid->GetGridWidth(); j++)
		{
			pgrid->DrawAtPixel(i, j, '-');

		}
	}

	for (int i = 1; i < pgrid->GetGridHeight(); i += 2)
	{
		for (int j = 0; j < pgrid->GetGridWidth(); j += 2)
		{
			pgrid->DrawAtPixel(i, j, '|');
		}
	}

	for (int i = 1; i <= 9; i++)
	{
		DrawAtCell(XO_values[i - 1], i);
	}
}
void XO::GameLoop()
{
	while (!isGameOver)
	{
		int choice = TakePlayerInput();
		XO_values[choice - 1] = player_symbol;
		DrawAtCell(player_symbol, choice);
		pconsole->Clear();
		pgrid->Draw();

		state = CheckWinDraw();

		switch (state)
		{

			case 1: //win
				std::cout << "Player (" << player_symbol << ") WON!!" << std::endl;
				isGameOver = true;
				break;

			case 0: //draw
				std::cout << "DRAW!!!!" << std::endl;
				isGameOver = true;
				break;

			case -1: //game did not end yet
				NextTurn();
				break;
		}

	}
}

void XO::DrawAtCell(char symbol, int cell)
{
	//1-9
	//-------
	//|1|2|3|
	//-------
	//|4|5|6|
	//-------
	//|7|8|9|
	//-------
	unsigned int x, y;

	if (cell <= 3) { x = 1; } //1 2 3
	else if (cell <= 6) { x = 3; } //4 5 6
	else if (cell <= 9) { x = 5; } //7 8 9

	//1 4 7  %3 = 1
	//2 5 8  %3 = 2
	//3 6 9  %3 = 0

	if (cell % 3 == 1) { y = 1; } //1 4 7 
	else if (cell % 3 == 2) { y = 3; } //4 5 6
	else if (cell % 3 == 0) { y = 5; } //7 8 9

	pgrid->DrawAtPixel(x, y, symbol);
}


unsigned int XO::TakePlayerInput()
{
	int player_choice = 0;

	std::cout << "choose cell 1 - 9: ";
	std::cin >> player_choice;

	if (player_choice >= 1 && player_choice <= 9) //must check that choice in boundary first
	{
		if ((XO_values[player_choice - 1] != 'X') && (XO_values[player_choice - 1] != 'O'))
		{
			return player_choice;
		}
		else
		{
			std::cout << "cell already taken, choose another: " << std::endl;
			TakePlayerInput();
		}
	}
	else
	{
		std::cout << "choose a valid input: ";
		TakePlayerInput();
	}
}

void XO::NextTurn()
{
	if (player_symbol == 'X') { player_symbol = 'O'; }
	else { player_symbol = 'X'; } //O
}

int XO::CheckWinDraw()
{
	//1 win, 0 draw, -1 game did not end yet

	bool win = false;


	for (int i = 0; i <= 6; i += 3)
	{
		//horizontal check
		if ((XO_values[i] == XO_values[i + 1]) && (XO_values[i] == XO_values[i + 2])) win = true;
	}

	for (int j = 0; j < 3; j++)
	{
		//vertial check
		if ((XO_values[j] == XO_values[j + 3]) && (XO_values[j] == XO_values[j + 6])) win = true;
	}

	if ((XO_values[0] == XO_values[4]) && (XO_values[0] == XO_values[8])) win = true;
	if ((XO_values[2] == XO_values[4]) && (XO_values[2] == XO_values[6])) win = true;


	if (win == true) { return 1; }
	else //no wins yet
	{
		//check either draw or game did not end
		if (IsAllCellsFull())
		{
			return 0; //draw
		}
		else
		{
			return -1; //game did not end yet
		}
	}

}

bool XO::IsAllCellsFull()
{
	for (int i = 0; i < 9; i++)
	{
		if ((XO_values[i] != 'X') && (XO_values[i] != 'O')) return false;
	}
	return true;
}