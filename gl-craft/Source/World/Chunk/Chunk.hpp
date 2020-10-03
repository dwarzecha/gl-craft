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
	void LoadSurrounding(std::shared_ptr<Chunk> adjacentChunk, int dirIter);

	void UpdateModel(glm::vec3 pos);
	void UpdateSectionModel(glm::vec3 pos, const std::vector<std::shared_ptr<Block> >* blocks, int dirIter);

	glm::vec3 GetPos() const;

	int GetMaxHeight() const;
	int GetMinHeight() const;
	int GetMaxSectionHeight(glm::vec3 pos) const;
	int GetMinSectionHeight(glm::vec3 pos) const;
	int GetMaxBorderHeight(DirIter dirIter) const;
	int GetMinBorderHeight(DirIter dirIter) const;

	std::shared_ptr<Block> GetBlock(glm::vec3 pos) const;
	const std::vector<std::shared_ptr<Block> >* GetSectionBlocks(glm::vec3 pos);
	std::vector<const std::vector<std::shared_ptr<Block> >* > GetBlocks() const;
	const std::vector<std::shared_ptr<ChunkSection> > GetSections() const;

	bool HasSurroundingLoadedAt(int dirIter);

	void SetBlock(glm::vec3 pos, BlockID id);

	bool hasModel = false;

private:
	void MakeSections();
	
	glm::vec3 WorldToChunkCoords(glm::vec3 pos) const;
	glm::vec3 ChunkToWorldCoords(glm::vec3 pos) const;
	
	glm::vec3 GetSectionCoords(glm::vec3 pos) const;
	int GetSectionIndex(glm::vec3 pos) const;

	bool OutOfBounds(glm::vec3 pos);

	ChunkPopulator m_populator;

	std::vector<std::shared_ptr<ChunkSection> > m_sections;
	std::vector<std::shared_ptr<Chunk> > m_surroundingChunks;

	glm::vec3 m_pos;
};

#endif // CHUNK_HPP_INCLUDED
