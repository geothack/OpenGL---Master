#pragma once

#include <GLFW/glfw3.h>

#include <string_view>
#include <print>

class glfwWindow
{
public:
	glfwWindow() = default;
	glfwWindow(std::string_view title, const int width, const int height);
	~glfwWindow();

	glfwWindow(const glfwWindow&) = delete;
	glfwWindow& operator=(glfwWindow&&) = delete;
	glfwWindow& operator=(const glfwWindow&) = delete;
	glfwWindow(glfwWindow&&) = delete;

	void Events() const;


private:
	GLFWwindow* mPlatformWindow;

};

