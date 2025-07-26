#pragma once

#include "glfwWindow.h"

class imgui
{
public:
	imgui() = default;
	imgui(glfwWindow& window);

	~imgui();

	void Render();

private:

};

