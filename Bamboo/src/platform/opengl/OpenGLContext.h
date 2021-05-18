#pragma once

#include "bamboo\renderer\GraphicsContext.h"

struct GLFWwindow;

namespace BAMBOO
{
	class OpenGLContext : public GraphicsContext
	{
	private:
		GLFWwindow* _WindowHandle;

	public:
		OpenGLContext(GLFWwindow* windowHandle);

	public:
		virtual void Init()override;
		virtual void SwapBuffers()override;
	};
}