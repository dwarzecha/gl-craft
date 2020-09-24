#ifndef CHUNKRENDERER_HPP_INCLUDED
#define CHUNKRENDERER_HPP_INCLUDED

#include <vector>
#include <map>
#include <memory>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "../World/Chunk/Chunk.hpp"
#include "../Texture/BasicTexture.hpp"

class ChunkRenderer
{
public:
	ChunkRenderer() = default;
	ChunkRenderer(std::shared_ptr<Chunk> chunk);

	void Add(std::shared_ptr<Chunk> chunk);
	void DrawQuads(const unsigned int& shaderProgram);

public:
	std::vector<std::shared_ptr<Chunk> > m_chunks;
};

#endif // CHUNKRENDERER_HPP_INCLUDED
