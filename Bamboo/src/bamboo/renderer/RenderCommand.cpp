#include "Base.h"
#include "RenderCommand.h"
#include "platform\opengl\OpenGLRendererAPI.h"

namespace BAMBOO
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}