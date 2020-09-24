#ifndef CHUNK_HPP_INCLUDED
#define CHUNK_HPP_INCLUDED

#include <vector>
#include <memory>

#include "glm/glm.hpp"

#include "../../Util/NonCopyable.hpp"
#include "../Block/Block.hpp"
#include "ChunkSection.hpp"
#include "ChunkPopulator.hpp"

class Chunk : public NonCopyable
{
public:
	Chunk(glm::vec3 pos);

	void Populate(std::vector<double> heightMap);
	void CreateModel();
	void LoadSurrounding(const std::vector<std::shared_ptr<ChunkSection> > surroundingSections, int dirIter);

	void UpdateModel(glm::vec3 pos);
	void UpdateSectionModel(glm::vec3 pos, const std::vector<Block>* blocks, int dirIter);

	glm::vec3 GetPos() const;
	Block GetBlock(glm::vec3 pos) const;
	const std::vector<Block>* GetSectionBlocks(glm::vec3 pos);
	std::vector<const std::vector<Block>* > GetBlocks() const;
	const std::vector<std::shared_ptr<ChunkSection> > GetSections() const;

	void SetBlock(glm::vec3 pos, BlockID id);

private:
	void MakeSections();
	
	glm::vec3 WorldToChunkCoords(glm::vec3 pos) const;
	glm::vec3 ChunkToWorldCoords(glm::vec3 pos) const;
	
	glm::vec3 GetSectionCoords(glm::vec3 pos) const;
	int GetSectionIndex(glm::vec3 pos) const;

	bool OutOfBounds(glm::vec3 pos);

	ChunkPopulator m_populator;

	std::vector<std::shared_ptr<ChunkSection> > m_sections;

	glm::vec3 m_pos;
};

#endif // CHUNK_HPP_INCLUDED
