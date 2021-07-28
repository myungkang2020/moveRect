#pragma once
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <deque>
#include <algorithm>
#include <chrono>

namespace moveRectconsole {

	typedef struct vec2 {
		int32_t x, y;
	}vec2;

	class Actor
	{
	public:
		Actor();
		int32_t update();

	private:
		int32_t Display();

		int32_t init();
		int32_t move();
		char getInput();

		int32_t saveBodyPosData();

		COORD headPos;
		std::deque<std::pair<uint32_t, uint32_t>> bodyPos;
		uint32_t currentBodyLength;
		bool isPrevAddBody;
		const uint32_t maxBodyLength = 50;
		std::chrono::system_clock::time_point prevFrameTime;
		
		char input;
	};
}

