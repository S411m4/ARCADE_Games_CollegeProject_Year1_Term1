#include <iostream>
#include <conio.h>
#include "SnakeGameClass.h"
#include <fstream>

//constructor 
SnakeGame::SnakeGame()
{   // dimensions of the game 
    pGrid = new Grid(height, width, 0, 0, ' ');
    pConsole = new Console;
    pConsole->HideCursor(); 
}

//destuctor
SnakeGame::~SnakeGame()
{
    delete pGrid;
    delete pConsole;
    pGrid = nullptr;
    pConsole = nullptr;
}

//'a' 's' 'd' 'w' keys that we will play the game with 
void SnakeGame::Input()
{
    char key;
    key = _getch();
    
    
    switch (key)
    {
    case 'a':
        dir = LEFT;
        break;
    case 'd':
        dir = RIGHT;
        break;
    case 'w':
        dir = UP;
        break;
    case 's':
        dir = DOWN;
        break;
        /*   case 'x':
               gameOver = true;*/
               //   break;

    }
}

//TODO: body position of snake
//Collide of snake --> DONE

void SnakeGame::GameAlgorithm()
{   //variables that will record the snake movement
    unsigned int prevX = tailX[0];
    unsigned int prevY = tailY[0];
    unsigned int prev2X, prev2Y;
    tailX[0] = x; //the beginning of the tail array will be the head
    tailY[0] = y;

    //to save the new movement that been taken by the user     
    for (int i = 1; i < nTail; i++) 
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir)
    {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;
     }

    //when collide with the wall --> return to the game from the other side
    if (x >= width)
        x = 0;
    else if (x < 0)
        x = width - 1;
        
    if (y >= height)
        y = 0;
    else if (y < 0)
        y = height - 1;
        
    //random postion of the apple "F"
    if (x == fruitX && y == fruitY) {
        //for every fruit eaten ; the score increases by 10 pionts 
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;

        //the tail also increases by "o"
        nTail++;
    }

    //when collide with itself --> game over
    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y) {
            gameOver = true;
            std::cout << "Game Over";
           // return;
        }
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

    if (gameOver)
    {
        std::fstream snakeScore("snakeScore.txt", std::ios::out | std::ios::app);
        if (snakeScore.is_open())
        {
            snakeScore << score << "\n";
        }
        snakeScore.close();
    }
}

//all the variables of the game (snake , apples , postions , score )
void SnakeGame::InitalizeGame()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}


// to draw the dimensions of the game & the apple & the snake's head and tail 
void SnakeGame::Draw()
{   //dimensions of the top row
    pGrid->Draw();

    for (int i = 0; i < width + 2; i++)
        std::cout << "#";
    std::cout << std::endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                //dimensions of the left side
                std::cout << "#";
            if (i == y && j == x)
                //the head of the snake
                std::cout << "O";
            else if (i == fruitY && j == fruitX)
                //the apple's position
                std::cout << "F";
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    //print "o" if the snake ate the apple 
                    if (tailX[k] == j && tailY[k] == i) {
                        std::cout << "o";
                        print = true;
                    }
                }
                // print blank if it didn't eat the apple
                if (!print)
                    std::cout << " ";
            }
            //dimensions of the right side
            if (j == width - 1)
                std::cout << "#";
        }
        std::cout << std::endl;
    }
    //dimensions of the bottom row
    for (int i = 0; i < width + 2; i++)
        std::cout << "#";

    std::cout << std::endl;
    std::cout << "Score:" << score << std::endl;
}