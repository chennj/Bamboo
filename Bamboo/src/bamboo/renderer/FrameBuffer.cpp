#include "Base.h"

#include "FrameBuffer.h"
#include "Renderer.h"
#include "platform\opengl\OpenGLFrameBuffer.h"

namespace BAMBOO
{
	Ref<FrameBuffer> FrameBuffer::Create(const FrameBufferSpecification & spec)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:	BB_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLFrameBuffer>(spec);
		}

		BB_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}