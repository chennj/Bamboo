#include "Base.h"

#include "Renderer.h"
#include "platform\opengl\OpenGLShader.h"
#include "bamboo\renderer\Renderer2D.h"

namespace BAMBOO
{
	Scope<Renderer::SceneData> Renderer::_SceneData = CreateScope<Renderer::SceneData>();

	void Renderer::BeginScene(Camera& camera)
	{
		_SceneData->ViewProjectionMatrix = camera.GetProjection();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, glm::mat4& transform)
	{
		// ����ɫ��
		shader->Bind();
		// Camera�任���߳�ΪͶӰ��ͼ�任���任���ǹ۲�㣬����������۲������
		// ����Camera�����ƶ��������������������ƶ�
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UpdateUniformMat4("u_ViewProjection",_SceneData->ViewProjectionMatrix);
		// Model�任���߳�Ϊģ�ͱ任���任�������屾��ֱ����������
		// ����Camera�̶�������ͨ�����ֱ任���������ֱ�������ƶ�
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UpdateUniformMat4("u_Model", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

	void Renderer::Init(const std::string & filePath)
	{
		BB_PROFILE_FUNCTION();

		RenderCommand::Init();
		Renderer2D::Init(filePath);
	}

	void Renderer::Init(const std::string & vertexFilePath, const std::string & fragmentFilePath)
	{
		BB_PROFILE_FUNCTION();

		RenderCommand::Init();
		Renderer2D::Init(vertexFilePath, fragmentFilePath);
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}
}