#include "Core/Core.h"
#include "Keyboard.h"

void Keyboard::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action != GLFW_RELEASE)
    {
        if (!mKeys[key])
        {
            mKeys[key] = true;
        }
    }
    else
    {
        mKeys[key] = false;
    }
    mKeysChanged[key] = action != GLFW_REPEAT;
}

bool Keyboard::Key(int key)
{
	return mKeys[key];
}

bool Keyboard::KeyChanged(int key)
{
	bool ret = mKeysChanged[key];
	mKeysChanged[key] = false;
	return ret;
}

bool Keyboard::KeyWentUp(int key)
{
	return !mKeys[key] && KeyChanged(key);
}

bool Keyboard::KeyWentDown(int key)
{
	return mKeys[key] && KeyChanged(key);
}
