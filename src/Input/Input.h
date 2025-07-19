#pragma once

#include "Input/Keyboard.h"

class Input
{
public:
	static Input* Get();

	bool Key(int key);

	bool KeyWentUp(int key);

	bool KeyWentDown(int key);

	void Free();

private:
	inline static Input* mInput = nullptr;

	Keyboard mKeyboard;
};

