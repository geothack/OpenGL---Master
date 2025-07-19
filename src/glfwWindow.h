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
	static void APIENTRY DebugLog(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char* message, const void* userParam);

private:
	GLFWwindow* mPlatformWindow;

};

