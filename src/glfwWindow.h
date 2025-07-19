#pragma once

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


	void SwapBuffers() const;

	GLFWwindow* const Get() const { return mPlatformWindow; }

private:
	GLFWwindow* mPlatformWindow;

};

