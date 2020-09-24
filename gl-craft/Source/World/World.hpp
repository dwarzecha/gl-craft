#ifndef WORLD_HPP_INCLUDED
#define WORLD_HPP_INCLUDED

#include <vector>
#include <memory>

#include "ChunkManager.hpp"
#include "WorldGenerator.hpp"

class World
{
public:
	World();

	void AddChunk(glm::vec3 pos);

	void Update(glm::vec3 playerPos, float visibilityRadius);
	void UpdateModel(glm::vec3 pos);

	const std::vector<std::shared_ptr<Chunk> >* GetChunks() const;
	Block GetBlock(glm::vec3 pos);

	void SetBlock(glm::vec3 pos, BlockID id);

private:
	bool OutOfBounds(glm::vec3 pos);
	bool ChunkExists(glm::vec3 pos);

	ChunkManager m_chunkManager;
	WorldGenerator m_generator;
};

#endif // WORLD_HPP_INCLUDED
