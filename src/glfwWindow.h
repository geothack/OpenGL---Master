#pragma once

struct Size
{
	int Width;
	int Height;
};


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

	GLFWwindow& const Get() const { return *mPlatformWindow; }

	const GLFWvidmode* GetVideoMode() const { return mVideoMode; }

	static Size GetSize() { return mWindowSize; }

private:
	static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
	static void APIENTRY DebugLog(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char* message, const void* userParam);

private:
	GLFWwindow* mPlatformWindow;
	const GLFWvidmode* mVideoMode;

	inline static Size mWindowSize = Size{};

};

