#pragma once

#include "bamboo\core\Layer.h"
#include "bamboo\events\ApplicationEvent.h"
#include "bamboo\events\MouseEvent.h"
#include "bamboo\events\KeyEvent.h"

namespace BAMBOO
{
	class BAMBOO_API ImGuiLayer : public Layer
	{
	private:
		float _Time = 0.0f;
		bool _BlockEvents = false;

	public:
		ImGuiLayer();
		~ImGuiLayer();

	public:
		virtual void OnAttach()override;
		virtual void OnDetach()override;
		virtual void OnImGuiRender()override;
		virtual void OnEvent(Event& e)override;

		void Begin();
		void End();

		void BlockEvents(bool block) { _BlockEvents = block; }
	};
}