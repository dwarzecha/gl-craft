#include "ChunkPopulator.hpp"

#include "../WorldConstants.hpp"

ChunkPopulator::ChunkPopulator(std::vector<std::shared_ptr<ChunkSection> >* sections)
	: m_sections(sections)
{
}

void ChunkPopulator::LoadData(std::vector<double> heightMap)
{
	m_heightMap = heightMap;
}

void ChunkPopulator::Populate()
{
	for (auto& section : *m_sections)
	{
		bool sectionEmpty = true;

		for (int i = 0; i < SECTION_SIZE; i++)
		for (int j = 0; j < SECTION_SIZE; j++)
		{
			if (section->GetPos().y < 64 + m_heightMap.at((section->GetPos().x + i) * CHUNK_SIZE + (section->GetPos().z + j)))
				sectionEmpty = false;
		}

		if (sectionEmpty)
		{
			section = nullptr;
		}
		else
		{
			for (int i = 0; i < SECTION_SIZE; i++)
			for (int j = 0; j < SECTION_SIZE; j++)
			for (int k = 0; k < SECTION_SIZE; k++)
			{
				double currentHeight = 64 + m_heightMap.at((section->GetPos().x + i) * CHUNK_SIZE + (section->GetPos().z + k));

				if (section->GetPos().y + j < currentHeight - 4)
					section->AddBlock(Block(BlockID::Stone, glm::vec3(i, j, k)));
				else if (section->GetPos().y + j < currentHeight - 1)
					section->AddBlock(Block(BlockID::Dirt, glm::vec3(i, j, k)));
				else if (section->GetPos().y + j < currentHeight)
					section->AddBlock(Block(BlockID::Grass, glm::vec3(i, j, k)));
				else
					section->AddBlock(Block(BlockID::Air, glm::vec3(i, j, k)));
			}
		}
	}
}