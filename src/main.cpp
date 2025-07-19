#include "glfwWindow.h"

int main()
{
    auto gameWindow = glfwWindow("OpenGl", 800, 600);

    while (true)
    {
        gameWindow.Events();
    }
}