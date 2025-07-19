#pragma once


class Keyboard
{
public:
    Keyboard() = default; 

    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    bool Key(int key);
    
    bool KeyChanged(int key);
    
    bool KeyWentUp(int key);

    bool KeyWentDown(int key);

private:
    inline static bool mKeys[GLFW_KEY_LAST] = { 0 };
    inline static bool mKeysChanged[GLFW_KEY_LAST] = { 0 };
};

