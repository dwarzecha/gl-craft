#include "RenderMaster.hpp"

#include "GL/glew.h"

void RenderMaster::Init(Camera* camera)
{
	m_camera = camera;

	m_shader.LoadShader();
	m_shader.UniformMatrix4fv(m_camera->GetProjectionMatrix(), "proj");
}

void RenderMaster::AddQuad(std::shared_ptr<Chunk> chunk)
{
	m_renderer.Add(chunk);
}

void RenderMaster::FinishRender()
{
	m_shader.UniformMatrix4fv(m_camera->GetViewMatrix(), "view");

	glClearColor(0.5f, 0.7f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_renderer.DrawQuads(m_shader.GetShaderProgram());
}