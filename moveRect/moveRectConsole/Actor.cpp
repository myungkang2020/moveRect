#include "Actor.h"

moveRectconsole::Actor::Actor()
{
	init();
}

int32_t moveRectconsole::Actor::update()
{
	using namespace std::chrono;

	if (duration_cast<milliseconds>(system_clock::now() - prevFrameTime) > static_cast<milliseconds>(60)) {
		move();
		saveBodyPosData();
		Display();
		prevFrameTime = system_clock::now();
	}

	return int32_t(0);
}

int32_t moveRectconsole::Actor::Display()
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), headPos);
	std::cout << 'o' << std::endl;



	return int32_t(0);
}

int32_t moveRectconsole::Actor::init()
{
	headPos.X = 30;
	headPos.Y = 20;
	currentBodyLength = 1;
	isPrevAddBody = false;
	bodyPos.push_front({ headPos.X, headPos.Y });
	prevFrameTime = std::chrono::system_clock::now();

	// Ä¿¼­ ±ôºýÀÓ Á¦°Å
	static HANDLE hOut;
	CONSOLE_CURSOR_INFO cInfo;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	cInfo.dwSize = 1;
	cInfo.bVisible = false;
	SetConsoleCursorInfo(hOut, &cInfo);

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), headPos);
	std::cout << "o" << std::endl;

	return int32_t(0);
}

int32_t moveRectconsole::Actor::move()
{
	static uint16_t moveWay = 0;

	if ((GetAsyncKeyState(87) & 0x0001) || GetAsyncKeyState(119) & 0x0001) {  moveWay = 1; } // W,w
	if ((GetAsyncKeyState(65) & 0x0001) || GetAsyncKeyState(97) & 0x0001) {  moveWay = 2; } // a,a
	if ((GetAsyncKeyState(83) & 0x0001) || GetAsyncKeyState(115) & 0x0001) {  moveWay = 3; } // s,s
	if ((GetAsyncKeyState(68) & 0x0001) || GetAsyncKeyState(100) & 0x0001) { moveWay = 4; } // d,d

	if ((GetAsyncKeyState(70) & 0x0001) || GetAsyncKeyState(102) & 0x0001) { currentBodyLength++; } // F,f
	if ((GetAsyncKeyState(82) & 0x0001) || GetAsyncKeyState(114) & 0x0001) { if (currentBodyLength > 1)currentBodyLength--; } // R,r

	switch (moveWay)
	{
	case 1:
		headPos.Y--;
		break;
	case 2:
		headPos.X--;
		break;
	case 3:
		headPos.Y++;
		break;
	case 4:
		headPos.X++;
		break;
	default:
		break;
	}

	headPos.X = headPos.X < 0 ? 0 : headPos.X;
	headPos.Y = headPos.Y < 0 ? 0 : headPos.Y;

	return 0;
}

char moveRectconsole::Actor::getInput()
{
	static char inputKey = 0;
	if (_kbhit())
	{
		inputKey = _getch();
	}

	return char(inputKey);
}

int32_t moveRectconsole::Actor::saveBodyPosData()
{
	uint32_t nowBodyLength = bodyPos.size();

	if (bodyPos.at(0).first != headPos.X || bodyPos.at(0).second != headPos.Y)
	{
		bodyPos.push_front({ headPos.X, headPos.Y });
		if (nowBodyLength < currentBodyLength) { isPrevAddBody = true; }
		else {
			COORD prevPos = { bodyPos.back().first, bodyPos.back().second };
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), prevPos);
			std::cout << " " << std::endl;
			bodyPos.pop_back();
		}
	}






	return int32_t(0);
}
