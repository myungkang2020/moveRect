#include "Actor.h"

moveRectconsole::Actor::Actor()
{
	init();
}

int32_t moveRectconsole::Actor::update()
{
	
	Display();

	return int32_t(0);
}

int32_t moveRectconsole::Actor::Display()
{

	COORD prevPos = pos;
	move();
	if(prevPos.X != pos.X || prevPos.Y != pos.Y)
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), prevPos);
		std::cout << " " << std::endl;

		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		std::cout << "o" << std::endl;
	}


	return int32_t(0);
}

int32_t moveRectconsole::Actor::init()
{
	pos.X = 30;
	pos.Y = 20;

	// Ä¿¼­ ±ôºýÀÓ Á¦°Å
	static HANDLE hOut;
	CONSOLE_CURSOR_INFO cInfo;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	cInfo.dwSize = 1;
	cInfo.bVisible = false;
	SetConsoleCursorInfo(hOut, &cInfo);

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	std::cout << "o" << std::endl;

	return int32_t(0);
}

int32_t moveRectconsole::Actor::move()
{
	char input = getInput();
	if ((GetAsyncKeyState(87) & 0x0001) || GetAsyncKeyState(119) & 0x0001) { pos.Y--; } // W,w
	if ((GetAsyncKeyState(65) & 0x0001) || GetAsyncKeyState(97) & 0x0001) { pos.X--; } // W,w
	if ((GetAsyncKeyState(83) & 0x0001) || GetAsyncKeyState(115) & 0x0001) { pos.Y++; } // W,w
	if ((GetAsyncKeyState(68) & 0x0001) || GetAsyncKeyState(100) & 0x0001) { pos.X++; } // W,w

	pos.X = pos.X < 0 ? 0 : pos.X;
	pos.Y = pos.Y < 0 ? 0 : pos.Y;

	return 0;
}

char moveRectconsole::Actor::getInput()
{
	char inputKey = 0;
	if (_kbhit())
	{
		inputKey = _getch();
	}

	return char(inputKey);
}
