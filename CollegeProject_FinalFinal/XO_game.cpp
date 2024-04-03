//#include "grid.h"
//#include "consoleutils.h"
//#include <iostream>
//
//////steps
//////1. draw grid shape
//////2. intialize game by numbers
//////3. take user input
//////4. check user input
//////5. if correct: draw at cell and next turn
//////- if not correct display message to user
//////6. repeat 3 - 5, till game end by draw or win
//
//void IntializeXOGrid(Grid& g, char* XO_values);
//void DrawAtCell(Grid& g, char symbol, int cell);
//unsigned int TakePlayerInput(char* XO_values);
//void NextTurn(char &player_symbol);
//bool IsAllCellsFull(char* XO_values);
//int CheckWinDraw(char* XO_values);
//
//
//
//int main()
//{
//	Console console;
//	Grid grid(7, 7, 20, 10, ' ');
//	char XO_values[9] = {'1','2','3','4','5','6','7','8','9'};
//
//	IntializeXOGrid(grid, XO_values);
//	grid.Draw();
//
//	bool isGameOver = false;
//	char player_symbol = 'X';
//	int state;
//	while (!isGameOver)
//	{
//		int choice = TakePlayerInput(XO_values); //1-9
//		XO_values[choice - 1] = player_symbol;
//		DrawAtCell(grid, player_symbol, choice);
//		console.Clear();
//		grid.Draw();
//
//		state = CheckWinDraw(XO_values);
//
//		switch (state)
//		{
//			case 1: //win
//				std::cout << "Player (" << player_symbol << ") WON!!" << std::endl;
//				isGameOver = true;
//				break;
//
//			case 0: //draw
//				std::cout << "DRAW!!!!" << std::endl;
//				isGameOver = true;
//				break;
//
//			case -1: //game did not end yet
//				NextTurn(player_symbol);
//				break;
//		}
//
//	}
//}
//
//void IntializeXOGrid(Grid& g, char* XO_values)
//{
//	
//	for (int i = 0; i < g.GetGridHeight(); i +=2) 
//	{
//		for (int j = 0; j < g.GetGridWidth(); j++)
//		{
//			g.DrawAtPixel(i, j, '-');
//
//		}
//	}
//	
//	for (int i = 1; i < g.GetGridHeight(); i += 2)
//	{
//		for (int j = 0; j < g.GetGridWidth(); j+=2)
//		{
//			g.DrawAtPixel(i, j, '|');
//		}
//	}
//
//	for (int i = 1; i <= 9; i++)
//	{
//		DrawAtCell(g, XO_values[i-1], i);
//	}
//}
//
//unsigned int TakePlayerInput(char* XO_values)
//{
//	int player_choice = 0;
//
//	std::cout << "choose cell 1 - 9: ";
//	std::cin >> player_choice;
//
//	if (player_choice >= 1 && player_choice <= 9) //must check that choice in boundary first
//	{
//		if ((XO_values[player_choice - 1] != 'X') && (XO_values[player_choice - 1] != 'O')) 
//		{
//			return player_choice;
//		}
//		else
//		{
//			std::cout << "cell already taken, choose another: " << std::endl;
//			TakePlayerInput(XO_values);
//		}
//	}
//	else
//	{
//		std::cout << "choose a valid input: ";
//		TakePlayerInput(XO_values);
//	}
//}
//
//void DrawAtCell(Grid& g, char symbol, int cell)
//{
//	//1-9
//	//-------
//	//|1|2|3|
//	//-------
//	//|4|5|6|
//	//-------
//	//|7|8|9|
//	//-------
//	unsigned int x, y;
//
//	if (cell <=  3) { x = 1; } //1 2 3
//	else if (cell <=  6) { x = 3; } //4 5 6
//	else if (cell <=  9) { x = 5; } //7 8 9
//
//	//1 4 7  %3 = 1
//	//2 5 8  %3 = 2
//	//3 6 9  %3 = 0
//
//	if (cell % 3 == 1) { y = 1; } //1 4 7 
//	else if (cell % 3 == 2) { y = 3; } //4 5 6
//	else if (cell % 3 == 0) { y = 5; } //7 8 9
//
//	g.DrawAtPixel(x, y, symbol);
//}
//
//void NextTurn(char &player_symbol)
//{
//	if (player_symbol == 'X') { player_symbol = 'O'; }
//	else { player_symbol = 'X'; } //O
//}
//
//int CheckWinDraw(char* XO_values)
//{
//	//1 win, 0 draw, -1 game did not end yet
//
//	bool win = false;
//
//
//	for (int i = 0; i <= 6; i += 3)
//	{
//		//horizontal check
//		if ((XO_values[i] == XO_values[i + 1]) && (XO_values[i] == XO_values[i + 2])) win = true;
//	}
//
//	for (int j = 0; j < 3; j++)
//	{
//		//vertial check
//		if ((XO_values[j] == XO_values[j + 3]) && (XO_values[j] == XO_values[j + 6])) win = true;
//	}
//
//	if ((XO_values[0] == XO_values[4]) && (XO_values[0] == XO_values[8])) win = true;
//	if ((XO_values[2] == XO_values[4]) && (XO_values[2] == XO_values[6])) win = true;
//
//
//	if (win == true) { return 1; }
//	else //no wins yet
//	{
//		//check either draw or game did not end
//		if (IsAllCellsFull(XO_values))
//		{
//			return 0; //draw
//		}
//		else
//		{
//			return -1; //game did not end yet
//		}
//	}
//
//}
//
//bool IsAllCellsFull(char* XO_values)
//{
//	for (int i = 0; i < 9; i++)
//	{
//		if ((XO_values[i] != 'X') && (XO_values[i] != 'O')) return false;
//	}
//	return true;
//}