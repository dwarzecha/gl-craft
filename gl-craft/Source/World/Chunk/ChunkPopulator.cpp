#include "ChunkPopulator.hpp"

#include "../WorldConstants.hpp"

#include <algorithm>

ChunkPopulator::ChunkPopulator(/*std::vector<std::shared_ptr<ChunkSection> >* sections*/)
	//: m_sections(sections)
{
}

void ChunkPopulator::LoadData(std::vector<double> heightMap)
{
	m_heightMap = heightMap;
}

void ChunkPopulator::Populate(std::vector<std::shared_ptr<ChunkSection> >* sections)
{
	for (auto& section : *sections)
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
			//section = nullptr;

			for (int i = 0; i < SECTION_SIZE; i++)
			for (int j = 0; j < SECTION_SIZE; j++)
			for (int k = 0; k < SECTION_SIZE; k++)
				section->AddBlock(nullptr);
		}
		else
		{
			for (int i = 0; i < SECTION_SIZE; i++)
			for (int j = 0; j < SECTION_SIZE; j++)
			for (int k = 0; k < SECTION_SIZE; k++)
			{
				double currentHeight = 64 + m_heightMap.at((section->GetPos().x + i) * CHUNK_SIZE + (section->GetPos().z + k));

				if (section->GetPos().y + j < currentHeight - 4)
					section->AddBlock(std::make_unique<Block>(BlockID::Stone, glm::vec3(i, j, k)));
				else if (section->GetPos().y + j < currentHeight - 1)
					section->AddBlock(std::make_unique<Block>(BlockID::Dirt, glm::vec3(i, j, k)));
				else if (section->GetPos().y + j < currentHeight)
					section->AddBlock(std::make_unique<Block>(BlockID::Grass, glm::vec3(i, j, k)));
				else
					section->AddBlock(nullptr);
			}
		}
	}
}

void ChunkPopulator::PopulateSection(std::shared_ptr<ChunkSection> section)
{
	for (int i = 0; i < SECTION_SIZE; i++)
	for (int j = 0; j < SECTION_SIZE; j++)
	for (int k = 0; k < SECTION_SIZE; k++)
	{
		double currentHeight = 64 + m_heightMap.at((section->GetPos().x + i) * CHUNK_SIZE + (section->GetPos().z + k));

		if (section->GetPos().y + j < currentHeight - 4)
			section->AddBlock(std::make_unique<Block>(BlockID::Stone, glm::vec3(i, j, k)));
		else if (section->GetPos().y + j < currentHeight - 1)
			section->AddBlock(std::make_unique<Block>(BlockID::Dirt, glm::vec3(i, j, k)));
		else if (section->GetPos().y + j < currentHeight)
			section->AddBlock(std::make_unique<Block>(BlockID::Grass, glm::vec3(i, j, k)));
		else
			section->AddBlock(nullptr);
	}
}

int ChunkPopulator::GetChunkHeight(int maxOrMin) const
{
	if (maxOrMin == 0)
		return 64 + *std::max_element(m_heightMap.begin(), m_heightMap.end());
	else
		return 64 + *std::min_element(m_heightMap.begin(), m_heightMap.end());
}

int ChunkPopulator::GetChunkSectionHeight(glm::vec3 pos, int maxOrMin) const
{
	std::vector<int> sectionHeightMap;

	for (int i = pos.x; i < pos.x + SECTION_SIZE; i++)
	for (int j = pos.z; j < pos.z + SECTION_SIZE; j++)
	{
		sectionHeightMap.push_back(m_heightMap.at(i * CHUNK_SIZE + j));
	}

	if (maxOrMin == 0)
		return 64 + *std::max_element(sectionHeightMap.begin(), sectionHeightMap.end());
	else
		return 64 + *std::min_element(sectionHeightMap.begin(), sectionHeightMap.end());
}

int ChunkPopulator::GetChunkBorderHeight(DirIter dirIter, int maxOrMin) const
{
	std::vector<int> borderHeightMap;

	for (int i = 0; i < CHUNK_SIZE; i++)
	{
		if (dirIter == DirIter::Front)
		{
			borderHeightMap.push_back(m_heightMap.at(i));
		}
		else if (dirIter == DirIter::Back)
		{
			borderHeightMap.push_back(m_heightMap.at(CHUNK_SIZE * (CHUNK_SIZE - 1) + i));
		}
		else if (dirIter == DirIter::Left)
		{
			borderHeightMap.push_back(m_heightMap.at(i * CHUNK_SIZE));
		}
		else if (dirIter == DirIter::Right)
		{
			borderHeightMap.push_back(m_heightMap.at(i * CHUNK_SIZE + CHUNK_SIZE - 1));
		}
	}

	if (maxOrMin == 0)
		return 64 + *std::max_element(borderHeightMap.begin(), borderHeightMap.end());
	else
		return 64 + *std::min_element(borderHeightMap.begin(), borderHeightMap.end());
}