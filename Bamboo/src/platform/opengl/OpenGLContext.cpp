#include "Base.h"

#include "OpenGLContext.h"

#include "glad\glad.h"
#include "GLFW\glfw3.h"

namespace BAMBOO
{
	OpenGLContext::OpenGLContext(GLFWwindow * windowHandle)
		: _WindowHandle(windowHandle)
	{
		BB_CORE_ASSERT(_WindowHandle, "Window handle is NULL!");
	}

	void OpenGLContext::Init()
	{
		BB_PROFILE_FUNCTION();

		glfwMakeContextCurrent(_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		BB_CORE_ASSERT(status, "Could not initialize GLAD");

		BB_CORE_INFO("OpenGL Info");
		BB_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		BB_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		BB_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		BB_PROFILE_FUNCTION();

		glfwSwapBuffers(_WindowHandle);
	}
}