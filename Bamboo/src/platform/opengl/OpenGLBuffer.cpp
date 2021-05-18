#include "Base.h"

#include "OpenGLBuffer.h"

#include "glad\glad.h"

namespace BAMBOO
{
	///////////////////////////////////////////////////////////////////////
	// VertexBuffer
	///////////////////////////////////////////////////////////////////////

	OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size)
	{
		BB_PROFILE_FUNCTION();

		//OpenGL version >= 4.5
		//glCreateBuffers(1, &_RendererID);
		glGenBuffers(1, &_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, _RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(float * vertices, uint32_t size)
	{
		BB_PROFILE_FUNCTION();

		//OpenGL version >= 4.5
		//glCreateBuffers(1, &_RendererID);
		glGenBuffers(1, &_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, _RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		BB_PROFILE_FUNCTION();

		glDeleteBuffers(1, &_RendererID);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		BB_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, _RendererID);
	}

	void OpenGLVertexBuffer::Unbind() const
	{
		BB_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexBuffer::SetData(const void * data, uint32_t size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, _RendererID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}

	///////////////////////////////////////////////////////////////////////
	// IndexBuffer
	///////////////////////////////////////////////////////////////////////

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t * indices, uint32_t count)
		:_Count(count)
	{
		BB_PROFILE_FUNCTION();

		//OpenGL version >= 4.5
		//glCreateBuffers(1, &_RendererID);
		glGenBuffers(1, &_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		BB_PROFILE_FUNCTION();

		glDeleteBuffers(1, &_RendererID);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		BB_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _RendererID);
	}

	void OpenGLIndexBuffer::Unbind() const
	{
		BB_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}