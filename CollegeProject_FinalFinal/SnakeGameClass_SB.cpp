#include "SnakeGameClass.h"
#include <iostream>
#include <conio.h>


SnakeGame::SnakeGame()
{
    pGrid = new Grid(height, width, 0, 0, ' ');
    pConsole = new Console;
    pConsole->HideCursor();

}

SnakeGame::~SnakeGame()
{
    delete pGrid;
    delete pConsole;
    pGrid = nullptr;
    pConsole = nullptr;
}

void SnakeGame::Input()
{
    char key;
    key = _getch();

    switch (key) {
    case 'a':
        x--;
        break;
    case 'd':
        x++;
        break;
    case 'w':
        y--;
        break;
    case 's':
        y++;
        break;

    case 'x':
        gameOver = true;
        break;
    default:
        break;
    }
}
//TODO: body position of snake
//Collide of snake

void SnakeGame::GameAlgorithm()
{
    unsigned int prevX = tailX[0];
    unsigned int prevY = tailY[0];
    unsigned int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    if (x >= width)
        x = 0;
    else if (x < 0)
        x = width - 1;

    if (y >= height)
        y = 0;
    else if (y < 0)
        y = height - 1;


    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }

   
    for (int i = 0; i < nTail; i++)
    {
        if (x == tailX[i] && y == tailY[i])
        {
            std::cout << "GAmeOVER" << std::endl;
        }
    }

    for (int i = 0; i < nTail; i++)
    {
        std::cout << tailY[i] << ",";
    }
        

    pGrid->DrawAtPixel(y, x, ' ');
}

void SnakeGame::GameLoop()
{
    while (!gameOver) {
        pConsole->Clear();
        Draw();
        Input();
        GameAlgorithm();
    }
}

void SnakeGame::InitalizeGame()
{
    gameOver = false;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;

    tailX[1] = x + 1;
    tailX[2] = x + 2;
    tailY[1] = y;
    tailY[2] = y;

    Draw();
}

void SnakeGame::Draw()
{
    for (int i = 0; i < width + 2; i++)
    std::cout << "#";
    std::cout << std::endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                std::cout << "#";
            if (i == y && j == x)
                std::cout << "O";
            else if (i == fruitY && j == fruitX)
                std::cout << "F";
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        std::cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    std::cout << " ";
            }

            if (j == width - 1)
                std::cout << "#";
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < width + 2; i++)
    std::cout << "#";
    std::cout << std::endl;
    std::cout << "Score:" << score << std::endl;

    pGrid->Draw();
}