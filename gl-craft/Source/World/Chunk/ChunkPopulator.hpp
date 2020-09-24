#ifndef CHUNKPOPULATOR_HPP_INCLUDED
#define CHUNKPOPULATOR_HPP_INCLUDED

#include "ChunkSection.hpp"

class ChunkPopulator
{
public:
	ChunkPopulator(std::vector<std::shared_ptr<ChunkSection> >* sections);
	void LoadData(std::vector<double> heightMap);
	void Populate();

private:
	std::vector<double> m_heightMap;
	std::vector<std::shared_ptr<ChunkSection> >* m_sections;
};

#endif // CHUNKPOPULATOR_HPP_INCLUDED