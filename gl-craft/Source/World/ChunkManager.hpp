#ifndef CHUNKMANAGER_HPP_INCLUDED
#define CHUNKMANAGER_HPP_INCLUDED

#include <vector>
#include <map>
#include <memory>

#include "Chunk/Chunk.hpp"
#include "../Maths/Perlin.hpp"

class ChunkManager
{
public:
	void LoadHeightMap(std::map<Perlin::Vector2D, double> heightMap);

	void CreateChunk(glm::vec3 pos);
	void GenModels();

	void UpdateModels(glm::vec3 pos);

	Block GetBlock(glm::vec3 pos);
	const std::vector<std::shared_ptr<Chunk> >* GetChunks() const;

	void SetBlock(glm::vec3 pos, BlockID id);

	bool OutOfBounds(glm::vec3 pos);

private:
	glm::vec3 GetChunkCoords(glm::vec3 pos) const;
	int GetChunkIndex(glm::vec3 pos) const;

	std::vector<std::shared_ptr<Chunk> > m_chunks;
	std::map<Perlin::Vector2D, double> m_heightMap;
};

#endif // CHUNKMANAGER_HPP_INCLUDED
