#pragma once

#include "Core.h"

namespace BAMBOO
{
	class BAMBOO_API Input
	{
	public:
		static bool IsKeyPressed(int keycode);

		static bool IsMouseButtonPressed(int keycode);

		static  std::pair<float, float> GetMousePosition();

		static float GetMouseX();

		static float GetMouseY();
	};
}