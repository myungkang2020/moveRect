#include "Actor.h"

namespace moveRectconsole {

	Actor::Actor()
	{
		init();
	}

	int32_t Actor::update()
	{
		using namespace std::chrono;

		if (duration_cast<milliseconds>(system_clock::now() - prevFrameTime) > static_cast<milliseconds>(60)) {
			inputHandler();
			changeBodyLength();
			Display();
			prevFrameTime = system_clock::now();
		}

		return int32_t(0);
	}

	int32_t Actor::Display()
	{
		COORD cursorPos = { bodyPos.front().first, bodyPos.front().second };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPos);
		std::cout << 'o' << std::endl;
		return int32_t(0);
	}

	int32_t Actor::init()
	{
		// init member variable
		headPos.X = 30;
		headPos.Y = 20;
		curMoveWay = 0;
		currentBodyLength = 1;
		isPrevAddBody = false;
		bodyPos.push_front({ headPos.X, headPos.Y });
		prevFrameTime = std::chrono::system_clock::now();
		width = 60;
		height = 40;
		
		DisplayBoundary();
		removeCursorFlicker();
		initBodyDisplay();
		

		return int32_t(0);
	}

	void Actor::removeCursorFlicker()
	{
		// Ä¿¼­ ±ôºýÀÓ Á¦°Å
		static HANDLE hOut;
		CONSOLE_CURSOR_INFO cInfo;

		hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		cInfo.dwSize = 1;
		cInfo.bVisible = false;
		SetConsoleCursorInfo(hOut, &cInfo);
	}

	void Actor::initBodyDisplay()
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), headPos);
		std::cout << "o" << std::endl;
	}

	void Actor::DisplayBoundary()
	{
		char borderCharacter1 = 95;
		char borderCharacter2 = 124;
		for (uint32_t i = 0; i < width; ++i) { std::cout << borderCharacter1; }
		std::cout << "\n";
		for (uint32_t i = 0; i < height - 2; ++i) {
			std::cout << borderCharacter2;
			for (uint32_t j = 0; j < width-2; ++j)
			{
				std::cout << " ";
			}
			std::cout << borderCharacter2 << "\n";
		}
		for (uint32_t i = 0; i < width; ++i) { std::cout << borderCharacter1; }
		std::cout << std::endl;
	}

	int32_t Actor::inputHandler()
	{
		if ((GetAsyncKeyState(87) & 0x0001) || GetAsyncKeyState(119) & 0x0001) { curMoveWay = 1; } // W,w
		if ((GetAsyncKeyState(65) & 0x0001) || GetAsyncKeyState(97) & 0x0001) { curMoveWay = 2; } // a,a
		if ((GetAsyncKeyState(83) & 0x0001) || GetAsyncKeyState(115) & 0x0001) { curMoveWay = 3; } // s,s
		if ((GetAsyncKeyState(68) & 0x0001) || GetAsyncKeyState(100) & 0x0001) { curMoveWay = 4; } // d,d

		if ((GetAsyncKeyState(70) & 0x0001) || GetAsyncKeyState(102) & 0x0001) { currentBodyLength++; } // F,f
		if ((GetAsyncKeyState(82) & 0x0001) || GetAsyncKeyState(114) & 0x0001) { if (currentBodyLength > 1)currentBodyLength--; } // R,r

		moveHead();

		return 0;
	}

	void Actor::moveHead()
	{
		switch (curMoveWay)
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
	}

	int32_t Actor::changeBodyLength()
	{
		uint32_t nowBodyLength = bodyPos.size();

		if (bodyPos.at(0).first != headPos.X || bodyPos.at(0).second != headPos.Y)
		{
			bodyPos.push_front({ headPos.X, headPos.Y });

			while (nowBodyLength > currentBodyLength)
			{
				COORD prevPos = { bodyPos.back().first, bodyPos.back().second };
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), prevPos);
				std::cout << " " << std::endl;
				bodyPos.pop_back();
				nowBodyLength = bodyPos.size();
			}
		}
		return int32_t(0);
	}

}

