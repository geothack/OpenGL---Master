#include "glfwWindow.h"

glfwWindow::glfwWindow(std::string_view title, const int width, const int height)
{
	auto success = glfwInit();

	if (success == 0)
	{
		std::println("Glfw failed to initialize");
	}

	mPlatformWindow = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);

	if (!mPlatformWindow)
	{
		std::println("Glfw failed to create window");
	}

	
}

glfwWindow::~glfwWindow()
{
	glfwDestroyWindow(mPlatformWindow);
	glfwTerminate();
}

void glfwWindow::Events() const
{
	glfwPollEvents();
}
