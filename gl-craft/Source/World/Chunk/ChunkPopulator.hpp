#ifndef CHUNKPOPULATOR_HPP_INCLUDED
#define CHUNKPOPULATOR_HPP_INCLUDED

#include "ChunkSection.hpp"
#include "../../Direction/Direction.hpp"

class ChunkPopulator
{
public:
	ChunkPopulator(/*std::vector<std::shared_ptr<ChunkSection> >* sections*/);
	void LoadData(std::vector<double> heightMap);
	void Populate(std::vector<std::shared_ptr<ChunkSection> >* sections);
	void PopulateSection(std::shared_ptr<ChunkSection> section);

	int GetChunkHeight(int maxOrMin) const;
	int GetChunkSectionHeight(glm::vec3 pos, int maxOrMin) const;
	int GetChunkBorderHeight(DirIter dirIter, int maxOrMin) const;

private:
	std::vector<double> m_heightMap;
	std::vector<BlockID> m_blockMap;
	std::vector<std::shared_ptr<ChunkSection> >* m_sections;
};

#endif // CHUNKPOPULATOR_HPP_INCLUDED