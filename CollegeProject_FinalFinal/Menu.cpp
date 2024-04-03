#include "Menu.h"
#include "drawShapes.h"
#include <conio.h>
#include <fstream>

Menu::Menu()
{
	pConsole = new Console;
	pArcadeGrid = new Grid(18, 96, 12, 1, ' ');
	pTitlesGrid = new Grid(10, 96, 12, 1, ' ');

	pHighScoreGrid = new Grid(28, 50, 15, 5, ' ');

	xo = new XOGame;
	snake = new SnakeGame;
	race = new RacingGame;



	pConsole->Clear();

	DrawArcade();
	pArcadeGrid->Draw();

	DrawTitles();
	pTitlesGrid->Draw();
}

Menu::~Menu()
{
	delete pArcadeGrid;
	delete pTitlesGrid;
	delete pConsole;
	delete xo;
	delete snake;
	delete race;

	pArcadeGrid = nullptr;
	pTitlesGrid = nullptr;
	pConsole = nullptr;
	xo = nullptr;
	snake = nullptr;
	race = nullptr;

}

void Menu::HighScoreScreen()
{

	//draw borders
	for (int i = 0; i < pHighScoreGrid->GetGridHeight(); i++)
	{
		for (int j = 0; j < pHighScoreGrid->GetGridWidth(); j++)
		{
			if (i == 0 || i == pHighScoreGrid->GetGridHeight() - 1) pHighScoreGrid->DrawAtPixel(i, j, '#');
			if (j == 0 || j == pHighScoreGrid->GetGridWidth() - 1) pHighScoreGrid->DrawAtPixel(i, j, '#');
		}
	}

	//delete previous game title
	for (int i = 2; i < 9; i++)
	{
		for (int j = 1; j < pHighScoreGrid->GetGridWidth() - 2;j++)
		{
			pHighScoreGrid->DrawAtPixel(i, j, ' ');
		}
	}

	int startX = 1, startY = 2;


	//clear previous scores
	for (int i = 8; i < 26; i++)
	{
		for (int j = 6; j < 48; j++)
		{
			pHighScoreGrid->DrawAtPixel(i, j, ' ');
		}
	}
	
	switch (currentGameLetter)
	{
		//score draw limit (8 - 26) : y, (10 : 48) x
		case 'X':
			startX = pHighScoreGrid->GetGridHeight() - 10;
			DrawXOTitle(pHighScoreGrid, startX, startY);

			{
				std::fstream xoScore("xoScore.txt");
				pHighScoreGrid->DrawTextAt(8, 10, "| x |");
				pHighScoreGrid->DrawTextAt(23, 10, "| o |");
				pHighScoreGrid->DrawTextAt(38, 10, "| d |");

				std::string x_score, o_score, d_score;

				xoScore >> x_score;
				xoScore >> o_score;
				xoScore >> d_score;

				pHighScoreGrid->DrawTextAt(8, 13, x_score);
				pHighScoreGrid->DrawTextAt(23, 13, o_score);
				pHighScoreGrid->DrawTextAt(38, 13, d_score);

				xoScore.close();
			}

			break;

		case 'S':
			startX = 12;
			DrawSnakeTitle(pHighScoreGrid, startX, startY);


			{
				std::fstream snakeScore("snakeScore.txt");
				std::string score;
				int counter = 0;

				while (!snakeScore.eof())
				{
					if (counter == 13)break; //limit is 14 in highscore board
					snakeScore >> score;
					pHighScoreGrid->DrawTextAt(10, 10 + counter, score);
					counter++;
				}
				snakeScore.close();

			}

			break;

		case 'R':
			startX = 14;
			DrawRaceTitle(pHighScoreGrid, startX, startY);

			
			{
				std::fstream raceScore("raceScore.txt");
				std::string score;
				int counter = 0;
				
				while (!raceScore.eof())
				{
					if (counter == 13)break; //limit is 14 in highscore board
					raceScore >> score;
					pHighScoreGrid->DrawTextAt(10, 10 + counter, score);
					counter++;
				}
				raceScore.close();

			}
			break;
	}

	pHighScoreGrid->Draw();

	std::cout << "Press z to return to Menu" << std::endl;

	while (_getch() != 'z'); //wait till user press z, then return to main menu
}

void Menu::TakeUserInput()
{
	while (!gameChosen)
	{
		char key = _getch();

		try
		{
			switch (key)
			{
			case 'd':
				chosenGameIndex++;
				break;
			case 'a':
				chosenGameIndex--;
				break;

			case 'x':
				ChooseGame();
				break;

			default:
				throw('e');
			}

			if (chosenGameIndex < 1) { chosenGameIndex = NoOfGames; }
			if (chosenGameIndex > NoOfGames) { chosenGameIndex = 1; }

			//clear previous line
			DrawLine(pTitlesGrid, 6, 7, 89, Horizontal, ' ');
			switch (chosenGameIndex)
			{
			case 1://XO
				DrawLine(pTitlesGrid, 6, 7, 15, Horizontal, '=');

				break;

			case 2://snake
				DrawLine(pTitlesGrid, 28, 7, 29, Horizontal, '=');
				break;

			case 3://race
				DrawLine(pTitlesGrid, 64, 7, 26, Horizontal, '=');
				break;

			}
		}
		catch (...)
		{
				//do nothing till user enter right input	
		}
		
		

		//return to menu
		pConsole->Clear();
		pArcadeGrid->Draw();
		pTitlesGrid->Draw();
	}
}

void Menu::ChooseGame()
{
	pConsole->Clear();
	gameChosen = true;

	switch (chosenGameIndex)
	{
	case 1://XO
		currentGameLetter = 'X';
		xo->IntializeGame();
		xo->GameLoop();
		break;

	case 2://snake
		currentGameLetter = 'S';
		snake->InitalizeGame();
		snake->GameLoop();
		break;

	case 3://race
		currentGameLetter = 'R';
		race->InitalizeGame();
		race->GameLoop();
		break;

	}


	if (gameChosen)
	{
		pConsole->Clear();

		//end screen
		HighScoreScreen();

		//choose another game after executing chosen game code
		//return to menu
		gameChosen = false;
		TakeUserInput();
	}

}

void Menu::DrawArcade()
{
	//draw borders
	for (int i = 0; i < pArcadeGrid->GetGridHeight(); i++)
	{
		for (int j = 0; j < pArcadeGrid->GetGridWidth(); j++)
		{
			if (i == 0 || i == pArcadeGrid->GetGridHeight() - 1)
				pArcadeGrid->DrawAtPixel(i, j, '*');

			if (j == 0 || j == pArcadeGrid->GetGridWidth() - 1)
				pArcadeGrid->DrawAtPixel(i, j, '*');
		}
	}

	//letter length: 3 - Height - 4
	// A width : 3 - 8

	int lettersStartX = 3, lettersStartY = 4,
	lettersEndX = pArcadeGrid->GetGridWidth() - 6, lettersEndY = pArcadeGrid->GetGridHeight() -7;
		
	//Draw A:
	//first vertical line
	DrawLine(pArcadeGrid, lettersStartX, lettersStartY+3, lettersEndY - lettersStartY, Vertical,'#');
	DrawLine(pArcadeGrid, lettersStartX+1, lettersStartY + 3, lettersEndY - lettersStartY, Vertical,'#');
	DrawLine(pArcadeGrid, lettersStartX+2, lettersStartY+3, lettersEndY-lettersStartY, Vertical,'#');
	//cap
	DrawLine(pArcadeGrid,lettersStartX+1, 6,11, Horizontal,'#');
	DrawLine(pArcadeGrid, lettersStartX+2, 5,9, Horizontal,'#');
	DrawLine(pArcadeGrid, lettersStartX+3, 4, 7, Horizontal,'#');
	//horizontal middle line
	DrawLine(pArcadeGrid, lettersStartX+3, 9, 7, Horizontal,'#');
	DrawLine(pArcadeGrid, lettersStartX+3, 10, 7, Horizontal,'#');
	//second vertical line
	DrawLine(pArcadeGrid, lettersStartX + 10, lettersStartY + 3, lettersEndY - lettersStartY, Vertical, '#');
	DrawLine(pArcadeGrid, lettersStartX + 1 + 10, lettersStartY + 3, lettersEndY - lettersStartY, Vertical, '#');
	DrawLine(pArcadeGrid, lettersStartX + 2 + 10, lettersStartY + 3, lettersEndY - lettersStartY, Vertical, '#');

	lettersStartX += (10 + 3+3);

	//Draw R:
	//first vertical line
	DrawLine(pArcadeGrid, lettersStartX, lettersStartY + 2, lettersEndY - lettersStartY+1, Vertical, '#');
	DrawLine(pArcadeGrid, lettersStartX + 1, lettersStartY + 2, lettersEndY - lettersStartY+1, Vertical, '#');
	DrawLine(pArcadeGrid, lettersStartX + 2, lettersStartY + 2, lettersEndY - lettersStartY+1, Vertical, '#');
	//horizontal line top
	DrawLine(pArcadeGrid, lettersStartX + 2, lettersStartY, 7, Horizontal, '#');
	DrawLine(pArcadeGrid, lettersStartX + 2, lettersStartY +1, 7, Horizontal, '#');
	//R circle
	DrawLine(pArcadeGrid, lettersStartX + 2 + 7, lettersStartY + 1, lettersEndY-lettersStartY+2, Vertical, '#');
	DrawLine(pArcadeGrid, lettersStartX + 2 + 8, lettersStartY + 2, 3, Vertical, '#');
	DrawLine(pArcadeGrid, lettersStartX + 2 + 9, lettersStartY + 3, 1, Vertical, '#');
	DrawLine(pArcadeGrid, lettersStartX + 3, lettersStartY + 4, 6, Horizontal, '#');
	//R second line
	DrawLine(pArcadeGrid, lettersStartX + 6, lettersStartY + 5, 1, Vertical, '#');
	DrawLine(pArcadeGrid, lettersStartX + 7, lettersStartY + 5, 3, Vertical, '#');
	DrawLine(pArcadeGrid, lettersStartX + 8, lettersStartY + 5, 5, Vertical, '#');
	DrawLine(pArcadeGrid, lettersStartX + 10, lettersStartY + 8, 2, Vertical, '#');
	DrawLine(pArcadeGrid, lettersStartX + 11, lettersStartY + 8, 2, Vertical, '#');

	lettersStartX += (11 + 3);

	//Draw C:
	//first vertical line
	DrawLine(pArcadeGrid, lettersStartX, lettersStartY+2, 6, Vertical, '#');
	DrawLine(pArcadeGrid, lettersStartX +1 , lettersStartY+1, 8, Vertical, '#');
	DrawLine(pArcadeGrid, lettersStartX +2 , lettersStartY, 9, Vertical, '#');
	//base
	DrawLine(pArcadeGrid, lettersStartX + 3, lettersEndY+2, 6, Horizontal, '#');
	DrawLine(pArcadeGrid, lettersStartX + 3, lettersEndY+1, 6, Horizontal, '#');
	//top
	DrawLine(pArcadeGrid, lettersStartX + 3, lettersStartY , 6, Horizontal, '#');
	DrawLine(pArcadeGrid, lettersStartX + 3, lettersStartY+1 , 6, Horizontal, '#');
	//outer circle up
	DrawLine(pArcadeGrid, lettersStartX + 9, lettersStartY+1, 2, Vertical, '#');
	DrawLine(pArcadeGrid, lettersStartX + 10, lettersStartY+2, 2, Vertical, '#');
	DrawLine(pArcadeGrid, lettersStartX + 11, lettersStartY+2, 2, Vertical, '#');
	//outer circle down
	DrawLine(pArcadeGrid, lettersStartX + 9, lettersEndY, 3, Vertical, '#');
	DrawLine(pArcadeGrid, lettersStartX + 10, lettersEndY-1, 3, Vertical, '#');
	DrawLine(pArcadeGrid, lettersStartX + 11, lettersEndY-1, 2, Vertical, '#');

	lettersStartX += (11 + 3);
	//Draw A:
	//first vertical line
	DrawLine(pArcadeGrid, lettersStartX, lettersStartY + 3, lettersEndY - lettersStartY, Vertical, '#');
	DrawLine(pArcadeGrid, lettersStartX + 1, lettersStartY + 3, lettersEndY - lettersStartY, Vertical, '#');
	DrawLine(pArcadeGrid, lettersStartX + 2, lettersStartY + 3, lettersEndY - lettersStartY, Vertical, '#');
	//cap
	DrawLine(pArcadeGrid, lettersStartX + 1, 6, 11, Horizontal, '#');
	DrawLine(pArcadeGrid, lettersStartX + 2, 5, 9, Horizontal, '#');
	DrawLine(pArcadeGrid, lettersStartX + 3, 4, 7, Horizontal, '#');
	//horizontal middle line
	DrawLine(pArcadeGrid, lettersStartX + 3, 9, 7, Horizontal, '#');
	DrawLine(pArcadeGrid, lettersStartX + 3, 10, 7, Horizontal, '#');
	//second vertical line
	DrawLine(pArcadeGrid, lettersStartX + 10, lettersStartY + 3, lettersEndY - lettersStartY, Vertical, '#');
	DrawLine(pArcadeGrid, lettersStartX + 1 + 10, lettersStartY + 3, lettersEndY - lettersStartY, Vertical, '#');
	DrawLine(pArcadeGrid, lettersStartX + 2 + 10, lettersStartY + 3, lettersEndY - lettersStartY, Vertical, '#');

	lettersStartX += (10 + 3 + 3);

	//Draw D:
	//first vertical line
	DrawLine(pArcadeGrid, lettersStartX, lettersStartY + 1, lettersEndY - lettersStartY+1, Vertical, '#');
	DrawLine(pArcadeGrid, lettersStartX + 1, lettersStartY + 1, lettersEndY - lettersStartY+1, Vertical, '#');
	DrawLine(pArcadeGrid, lettersStartX + 2, lettersStartY + 1, lettersEndY - lettersStartY+1, Vertical, '#');
	//circle
	DrawLine(pArcadeGrid, lettersStartX + 2, lettersStartY, 7, Horizontal, '#');
	DrawLine(pArcadeGrid, lettersStartX + 3, lettersStartY+1, 8, Horizontal, '#');
	DrawLine(pArcadeGrid, lettersStartX + 9, lettersStartY+1, lettersEndY-4, Vertical, '#');
	DrawLine(pArcadeGrid, lettersStartX + 10, lettersStartY+1, lettersEndY-4, Vertical, '#');
	DrawLine(pArcadeGrid, lettersStartX + 11, lettersStartY+2, lettersEndY-6, Vertical, '#');
	DrawLine(pArcadeGrid, lettersStartX + 12, lettersStartY+3, lettersEndY-8, Vertical, '#');
	DrawLine(pArcadeGrid, lettersStartX + 3, lettersEndY+1, 7, Horizontal, '#');
	DrawLine(pArcadeGrid, lettersStartX, lettersEndY+2, 8, Horizontal, '#');

	lettersStartX += (12 + 4);
	//Draw E:
	//first vertical line
	DrawLine(pArcadeGrid, lettersStartX, lettersStartY, lettersEndY - lettersStartY + 3, Vertical, '#');
	DrawLine(pArcadeGrid, lettersStartX + 1, lettersStartY, lettersEndY - lettersStartY + 3 ,Vertical, '#');
	DrawLine(pArcadeGrid, lettersStartX + 2, lettersStartY, lettersEndY - lettersStartY + 3, Vertical, '#');
	//first horizontal
	DrawLine(pArcadeGrid, lettersStartX+3, lettersStartY, 11, Horizontal, '#');
	DrawLine(pArcadeGrid, lettersStartX+3, lettersStartY+1, 11, Horizontal, '#');
	//second horizontal
	DrawLine(pArcadeGrid, lettersStartX + 3, lettersStartY+4, 11, Horizontal, '#');
	DrawLine(pArcadeGrid, lettersStartX + 3, lettersStartY + 5, 11, Horizontal, '#');
	//third horizontal
	DrawLine(pArcadeGrid, lettersStartX + 3, lettersStartY + 8, 11, Horizontal, '#');
	DrawLine(pArcadeGrid, lettersStartX + 3, lettersStartY + 9, 11, Horizontal, '#');
}

void Menu::DrawTitles()
{
	int startY = 2, EndY= pTitlesGrid->GetGridHeight()-1-1,
		startX =7, endX = pTitlesGrid->GetGridWidth()-6-1;

	//draw borders
	for (int i = 0; i < pTitlesGrid->GetGridHeight(); i++)
	{
		for (int j = 0; j < pTitlesGrid->GetGridWidth(); j++)
		{
			if (i == 0 || i == pTitlesGrid->GetGridHeight() - 1)
				pTitlesGrid->DrawAtPixel(i, j, '*');

			if (j == 0 || j == pTitlesGrid->GetGridWidth() - 1)
				pTitlesGrid->DrawAtPixel(i, j, '*');
		}
	}

	
	DrawXOTitle(pTitlesGrid, startX, startY);

	startX += (5 + 10);
	
	DrawSnakeTitle(pTitlesGrid, startX, startY);

	startX += (23 + 13);

	DrawRaceTitle(pTitlesGrid, startX, startY);
	
}


void Menu::DrawXOTitle(Grid* pGrid, int &startX, int &startY)
{
	//XO word
	//X:
	DrawLine(pGrid, startX, startY, 2, Horizontal, '#');
	DrawLine(pGrid, startX + 4, startY, 2, Horizontal, '#');
	DrawLine(pGrid, startX + 1, startY + 1, 4, Horizontal, '#');
	DrawLine(pGrid, startX + 2, startY + 2, 2, Horizontal, '#');
	DrawLine(pGrid, startX + 1, startY + 3, 4, Horizontal, '#');
	DrawLine(pGrid, startX, startY + 4, 2, Horizontal, '#');
	DrawLine(pGrid, startX + 4, startY + 4, 2, Horizontal, '#');

	startX += (4 + 3);
	//O:
	DrawLine(pGrid, startX, startY + 1, 3, Vertical, '#');
	DrawLine(pGrid, startX + 1, startY, 4, Horizontal, '#');
	DrawLine(pGrid, startX + 1, startY + 4, 4, Horizontal, '#');
	DrawLine(pGrid, startX + 5, startY + 1, 3, Vertical, '#');
}

void Menu::DrawSnakeTitle(Grid *pGrid,int &startX, int &startY)
{
	//draw snake
	//S:
	DrawLine(pGrid, startX + 1, startY, 3, Horizontal, '#');
	DrawLine(pGrid, startX, startY + 1, 1, Vertical, '#');
	DrawLine(pGrid, startX + 1, startY + 2, 2, Horizontal, '#');
	DrawLine(pGrid, startX + 3, startY + 3, 1, Horizontal, '#');
	DrawLine(pGrid, startX, startY + 4, 3, Horizontal, '#');
	//N:
	DrawLine(pGrid, startX + 5, startY, 5, Vertical, '#');
	DrawLine(pGrid, startX + 6, startY, 2, Vertical, '#');
	DrawLine(pGrid, startX + 7, startY + 1, 2, Vertical, '#');
	DrawLine(pGrid, startX + 8, startY + 2, 2, Vertical, '#');
	DrawLine(pGrid, startX + 9, startY, 5, Vertical, '#');
	//A:
	DrawLine(pGrid, startX + 11, startY, 5, Vertical, '#');
	DrawLine(pGrid, startX + 12, startY, 3, Horizontal, '#');
	DrawLine(pGrid, startX + 12, startY + 2, 3, Horizontal, '#');
	DrawLine(pGrid, startX + 15, startY, 5, Vertical, '#');
	//K:
	DrawLine(pGrid, startX + 17, startY, 5, Vertical, '#');
	DrawLine(pGrid, startX + 18, startY + 2, 1, Vertical, '#');
	DrawLine(pGrid, startX + 19, startY + 1, 2, Vertical, '#');
	DrawLine(pGrid, startX + 20, startY, 2, Vertical, '#');
	DrawLine(pGrid, startX + 20, startY + 3, 2, Vertical, '#');
	//E:
	DrawLine(pGrid, startX + 22, startY, 5, Vertical, '#');
	DrawLine(pGrid, startX + 23, startY, 4, Horizontal, '#');
	DrawLine(pGrid, startX + 23, startY + 2, 4, Horizontal, '#');
	DrawLine(pGrid, startX + 23, startY + 4, 4, Horizontal, '#');
}

void Menu::DrawRaceTitle(Grid *pGrid, int &startX, int &startY)
{
	//Race
	//R
	DrawLine(pGrid, startX, startY, 5, Vertical, '#');
	DrawLine(pGrid, startX + 1, startY, 4, Horizontal, '#');
	DrawLine(pGrid, startX + 5, startY + 1, 1, Vertical, '#');
	DrawLine(pGrid, startX + 1, startY + 2, 4, Horizontal, '#');
	DrawLine(pGrid, startX + 3, startY + 3, 1, Vertical, '#');
	DrawLine(pGrid, startX + 4, startY + 4, 1, Vertical, '#');
	//A
	DrawLine(pGrid, startX + 7, startY, 5, Vertical, '#');
	DrawLine(pGrid, startX + 8, startY, 3, Horizontal, '#');
	DrawLine(pGrid, startX + 8, startY + 2, 3, Horizontal, '#');
	DrawLine(pGrid, startX + 11, startY, 5, Vertical, '#');
	//C:
	DrawLine(pGrid, startX + 13, startY + 1, 3, Vertical, '#');
	DrawLine(pGrid, startX + 14, startY, 4, Horizontal, '#');
	DrawLine(pGrid, startX + 14, startY + 4, 4, Horizontal, '#');
	//E:
	DrawLine(pGrid, startX + 19, startY, 5, Vertical, '#');
	DrawLine(pGrid, startX + 20, startY, 4, Horizontal, '#');
	DrawLine(pGrid, startX + 20, startY + 2, 4, Horizontal, '#');
	DrawLine(pGrid, startX + 20, startY + 4, 4, Horizontal, '#');
}