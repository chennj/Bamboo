#pragma once

#include "RenderCommand.h"

#include "Camera.h"
#include "Shader.h"

namespace BAMBOO
{
	class Renderer
	{
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};
		static Scope<SceneData> _SceneData;

	public:
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

		static void BeginScene(Camera& camera);
		static void EndScene();

		static void Submit(
			const Ref<Shader>& shader, 
			const Ref<VertexArray>& vertexArray,
			glm::mat4& transform = glm::mat4(1.0f));

		static void Init(const std::string& filePath);
		static void Init(const std::string& vertexFilePath , const std::string& fragmentFilePath);

		static void OnWindowResize(uint32_t width, uint32_t height);
	};
}