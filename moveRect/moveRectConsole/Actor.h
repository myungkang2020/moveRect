#pragma once
#include <iostream>
#include <conio.h>
#include <Windows.h>

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

		COORD pos;
		char input;
	};
}

