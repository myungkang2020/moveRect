#pragma once
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <deque>
#include <algorithm>
#include <chrono>

namespace moveRectconsole {
	class Actor
	{
	public:
		Actor();
		int32_t update();

	private:
		int32_t Display();
		int32_t init();
		void removeCursorFlicker();
		void initBodyDisplay();
		void DisplayBoundary();
		int32_t inputHandler();
		void moveHead();

		int32_t changeBodyLength();

		COORD headPos;
		uint16_t curMoveWay;
		std::deque<std::pair<uint32_t, uint32_t>> bodyPos;
		uint32_t currentBodyLength;
		bool isPrevAddBody;
		const uint32_t maxBodyLength = 50;

		int32_t width, height;

		std::chrono::system_clock::time_point prevFrameTime;		
		char input;
	};
}

