#include "Core/Core.h"
#include "glfwWindow.h"
#include "Input/Input.h"
#include "Core/Error.h"

glfwWindow::glfwWindow(std::string_view title, const int width, const int height)
{
	auto success = glfwInit();

	if (success == 0)
	{
		Error error("Glfw failed to initialize");
	}

	mPlatformWindow = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);

	if (!mPlatformWindow)
	{
		Error error("Glfw failed to create window");
	}

	glfwMakeContextCurrent(mPlatformWindow);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
	{
		Error error("Failed to initialize glad");
	}

	glfwSetKeyCallback(mPlatformWindow, Keyboard::KeyCallback);

	glfwSwapInterval(1);

	mWindowSize.Width = width;
	mWindowSize.Height = height;

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(DebugLog, nullptr);
}

glfwWindow::~glfwWindow()
{
	glfwDestroyWindow(mPlatformWindow);
	glfwTerminate();
}

void glfwWindow::Events() const
{
	glfwPollEvents();

	if (GInput->KeyWentDown(GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(mPlatformWindow, true);
	}
}

void glfwWindow::SwapBuffers() const
{
	glfwSwapBuffers(mPlatformWindow);
}

void glfwWindow::DebugLog(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char* message, const void* userParam)
{
	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:
		std::println("OpenGL High {}", message);
		break;

	case GL_DEBUG_SEVERITY_MEDIUM:
		std::println("OpenGL Medium {}", message);
		break;

	case GL_DEBUG_SEVERITY_LOW:
		std::println("OpenGL Low {}", message);
		break;

	case GL_DEBUG_SEVERITY_NOTIFICATION:
		std::println("OpenGL Notification {}", message);
		break;

	default:

		break;
	}
}