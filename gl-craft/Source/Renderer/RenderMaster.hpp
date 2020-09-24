#ifndef RENDERMASTER_HPP_INCLUDED
#define RENDERMASTER_HPP_INCLUDED

#include <memory>

#include "ChunkRenderer.hpp"

#include "../Shader/BasicShader.hpp"
#include "../Entity//Camera/Camera.hpp"

class RenderMaster
{
public:
	void Init(Camera* camera);

	void AddQuad(std::shared_ptr<Chunk> chunk);
	void FinishRender();

private:
    ChunkRenderer m_renderer;

	BasicShader m_shader;
	Camera* m_camera;
};

#endif // RENDERMASTER_HPP_INCLUDED
