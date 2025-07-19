#include "Core/Core.h"
#include "Input.h"

Input* Input::Get()
{
	if (!mInput)
	{
		mInput = new Input();
	}

	return mInput;
}

bool Input::Key(int key)
{
    return mKeyboard.Key(key);
}

bool Input::KeyWentUp(int key)
{
    return mKeyboard.KeyWentUp(key);
}

bool Input::KeyWentDown(int key)
{
    return mKeyboard.KeyWentDown(key);
}

void Input::Free()
{
	delete mInput;
}
