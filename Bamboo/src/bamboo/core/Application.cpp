#include "Base.h"
#include "Application.h"

#include "bamboo\core\Log.h"
#include "glad\glad.h"
#include "GLFW\glfw3.h"

#include "bamboo\renderer\Renderer.h"

#include "Input.h"

namespace BAMBOO
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		Application("../Bamboo/assets/shaders/Texture.glsl");
	}

	Application::Application(const std::string & filePath, const std::string& name)
	{
		BB_PROFILE_FUNCTION();

		BB_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		_Window = Window::Create(WindowProps(name));
		_Window->SetEventCallback(BB_BIND_EVENT_FN(Application::OnEvent));
		//设置刷新频率是否垂直同步
		_Window->SetVSync(true);

		Renderer::Init(filePath);

		_ImGuiLayer = new ImGuiLayer();
		PushOverlay(_ImGuiLayer);
	}

	Application::~Application()
	{
		BB_PROFILE_FUNCTION();
	}

	void Application::OnEvent(Event& e)
	{
		BB_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		//dispatcher.Dispatch<WindowCloseEvent>([this](WindowCloseEvent& e1)->bool
		//{
		//	return this->OnWindowClose(e1);
		//});
		dispatcher.Dispatch<WindowCloseEvent>(BB_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BB_BIND_EVENT_FN(Application::OnWindowResize));

		//BB_CORE_TRACE("{0}",e);

		//for (auto it = _LayerStack.end(); it != _LayerStack.begin();)
		//{
		//	(*--it)->OnEvent(e);
		//	if (e._Handled)
		//		break;
		//}

		for (auto it = _LayerStack.begin(); it != _LayerStack.end(); it++)
		{
			if (e._Handled)
				break;
			(*it)->OnEvent(e);
		}
	}

	void Application::Close()
	{
		_Running = false;
	}

	void Application::Run()
	{
		BB_PROFILE_FUNCTION();

		while (_Running)
		{
			BB_PROFILE_SCOPE("RunLoop");

			float time = (float)glfwGetTime();
			Timestep timestep = time - _LastFrameTime;

			_LastFrameTime = time;

			if (!_Minimized)
			{
				{
					BB_PROFILE_SCOPE("LayerStack OnUpdate");

					for (Layer* layer : _LayerStack)
					{
						layer->OnUpdate(timestep);
					}
				}

				_ImGuiLayer->Begin();
				{
					BB_PROFILE_SCOPE("LayStack OnImGuiRender");

					for (Layer* layer : _LayerStack)
					{
						layer->OnImGuiRender();
					}
				}
				_ImGuiLayer->End();
			}


			_Window->OnUpdate();

		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent & e)
	{
		BB_PROFILE_FUNCTION();

		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			_Minimized = true;
			return false;
		}

		_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}

	void Application::PushLayer(Layer* layer)
	{
		BB_PROFILE_FUNCTION();

		_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		BB_PROFILE_FUNCTION();

		_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}
}
