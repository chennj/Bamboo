#pragma once

namespace BAMBOO
{
	class GraphicsContext
	{
	private:

	public:
		virtual ~GraphicsContext() = default;

	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}