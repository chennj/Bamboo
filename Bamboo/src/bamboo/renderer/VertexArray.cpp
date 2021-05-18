#include "Base.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "platform\opengl\OpenGLVertexArray.h"

namespace BAMBOO
{
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:	BB_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLVertexArray>();
		}

		BB_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}