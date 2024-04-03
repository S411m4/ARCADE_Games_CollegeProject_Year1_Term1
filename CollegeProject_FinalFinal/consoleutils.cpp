#include "consoleutils.h"
#include <iostream>

Console::Console()
{

}
void Console::Clear()
{ 
	std::cout << "\x1B[2J\x1B[H";
}

void Console::HideCursor()
{
	std::cout << "\x1B[?25l";
}

void Console::ShowCursor()
{
	std::cout << "\x1B[?25h";
}