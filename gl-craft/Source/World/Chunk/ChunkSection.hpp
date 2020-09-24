#ifndef CHUNKSECTION_HPP_INCLUDED
#define CHUNKSECTION_HPP_INCLUDED

#include <memory>

#include "glm/glm.hpp"

#include "ChunkModelGenerator.hpp"

class ChunkSection : public NonCopyable
{
public:
	ChunkSection(glm::vec3 pos);

	void AddBlock(const Block& block);

	void LoadSurrounding(const std::vector<Block>* surroundingBlocks, int dirIter);

	void CreateModel();
	void Bind();

	glm::vec3 GetPos();
	Block GetBlock(glm::vec3 pos) const;
	std::vector<std::unique_ptr<BlockFace> >* GetFaces();
	const std::vector<Block>* GetBlocks() const;

	void SetBlock(glm::vec3 pos, BlockID id);

private:
	glm::vec3 ChunkToSectionCoords(glm::vec3 pos) const;
	glm::vec3 SectionToChunkCoords(glm::vec3 pos) const;

	ChunkModelGenerator m_generator;

	std::unique_ptr<Model> m_model;

	glm::vec3 m_pos;
};

#endif // CHUNKSECTION_HPP_INCLUDED