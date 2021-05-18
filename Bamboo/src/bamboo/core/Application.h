#pragma once

#include "Core.h"

#include "Window.h"
#include "LayerStack.h"
#include "bamboo\events\Event.h"
#include "bamboo\events\ApplicationEvent.h"

#include "bamboo\core\Timestep.h"

#include "bamboo\imgui\ImGuiLayer.h"

namespace BAMBOO
{
	class Application
	{
	private:
		Scope<Window> _Window;
		ImGuiLayer* _ImGuiLayer;
		bool _Running = true;
		LayerStack _LayerStack;

		float _LastFrameTime = 0.0f;
		bool _Minimized = false;

	private:
		static Application* s_Instance;

	public:
		Application();
		Application(const std::string& filePath, const std::string& name="");
		virtual ~Application();

	public:
		void Run();

		void OnEvent(Event& e);
		void Close();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() const { return *_Window; }
		inline ImGuiLayer* GetImGuiLayer() { return _ImGuiLayer; }
		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	};

	// To be define in CLIENT
	Application* CreateApplication();
}

