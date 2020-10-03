#include "Chunk.hpp"

#include <algorithm>

#include "../WorldConstants.hpp"
#include "../../Direction/Direction.hpp"

Chunk::Chunk(glm::vec3 pos)
	: m_pos(pos), m_populator(&m_sections)
{
	for (int i = 0; i < 6; i++)
	{
		m_surroundingChunks.push_back(nullptr);
	}

	MakeSections();
}

void Chunk::Populate(std::vector<double> heightMap)
{
	m_populator.LoadData(heightMap);
	m_populator.Populate();
}

void Chunk::CreateModel()
{
	for (auto& section : m_sections)
	{
		if (section != nullptr)
		{
			int borderDir = section->OnBorder();

			if (borderDir == -1)
			{
				if (section->GetPos().y >= GetMinHeight() - SECTION_SIZE && section->GetPos().y <= GetMaxHeight()) section->CreateModel();
			}
			else
			{
				std::shared_ptr<Chunk> adjacentChunk = m_surroundingChunks.at(borderDir);

				if (adjacentChunk != nullptr)
				{
					bool secOnXBorder = (section->GetPos().x == 8);
					if (section->GetPos().y >= std::min(GetMinHeight(), m_surroundingChunks.at(borderDir)->GetMinHeight()) - SECTION_SIZE && section->GetPos().y <= std::max(GetMaxHeight(), m_surroundingChunks.at(borderDir)->GetMaxHeight())) section->CreateModel();
				}
				else
				{
					if (section->GetPos().y >= GetMinHeight() - SECTION_SIZE && section->GetPos().y <= GetMaxHeight()) section->CreateModel();
				}
			}
		}
	}

	hasModel = true;
}

void Chunk::LoadSurrounding(std::shared_ptr<Chunk> adjacentChunk, int dirIter)
{
	m_surroundingChunks.at(dirIter) = adjacentChunk;

	for (auto& section : m_sections)
	{
		if (section != nullptr)
		{
			glm::vec3 checkingPos = section->GetPos()
				+ Direction::directions.at(dirIter)
				* static_cast<float>(SECTION_SIZE);

			if (checkingPos.y < 0.0f) section->LoadSurrounding(nullptr, dirIter);
			else if (checkingPos.y > static_cast<float>(CHUNK_HEIGHT - SECTION_SIZE)) section->LoadSurrounding(nullptr, dirIter);
			else if (OutOfBounds(checkingPos))
			{
				if (checkingPos.x < 0.0f) checkingPos.x = CHUNK_SIZE - SECTION_SIZE;
				if (checkingPos.z < 0.0f) checkingPos.z = CHUNK_SIZE - SECTION_SIZE;
				if (checkingPos.x > static_cast<float>(CHUNK_SIZE - SECTION_SIZE)) checkingPos.x = 0.0f;
				if (checkingPos.z > static_cast<float>(CHUNK_SIZE - SECTION_SIZE)) checkingPos.z = 0.0f;

				int adjIndex = GetSectionIndex(checkingPos);
				if (adjIndex != -1)
				{
					if (adjacentChunk != nullptr)
						section->LoadSurrounding(adjacentChunk->GetSections().at(adjIndex)->GetBlocks(), dirIter);
					else
						section->LoadSurrounding(nullptr, dirIter);
				}
				else
				{
					section->LoadSurrounding(nullptr, dirIter);
				}
			}
			else
			{
				int index = GetSectionIndex(checkingPos);
				if (m_sections.at(index) != nullptr) section->LoadSurrounding(m_sections.at(index)->GetBlocks(), dirIter);
			}
		}
	}
}

void Chunk::UpdateModel(glm::vec3 pos)
{
	glm::vec3 chunkPos = WorldToChunkCoords(pos);
	glm::vec3 secPos = glm::vec3(static_cast<int>(chunkPos.x) % SECTION_SIZE, static_cast<int>(chunkPos.y) % SECTION_SIZE, static_cast<int>(chunkPos.z) % SECTION_SIZE);

	std::shared_ptr<ChunkSection> section = m_sections.at(GetSectionIndex(GetSectionCoords(chunkPos)));

	if (section != nullptr)
	{
		if (secPos.x == 0 && chunkPos.x != 0)
			UpdateSectionModel(pos + Direction::left, section->GetBlocks(), 3);

		if (secPos.y == 0 && chunkPos.y != 0)
			UpdateSectionModel(pos + Direction::down, section->GetBlocks(), 4);

		if (secPos.z == 0 && chunkPos.z != 0)
			UpdateSectionModel(pos + Direction::front, section->GetBlocks(), 1);

		if (secPos.x == SECTION_SIZE - 1 && chunkPos.x != CHUNK_SIZE - 1)
			UpdateSectionModel(pos + Direction::right, section->GetBlocks(), 2);

		if (secPos.y == SECTION_SIZE - 1 && chunkPos.y != CHUNK_HEIGHT - 1)
			UpdateSectionModel(pos + Direction::up, section->GetBlocks(), 5);

		if (secPos.z == SECTION_SIZE - 1 && chunkPos.z != CHUNK_SIZE - 1)
			UpdateSectionModel(pos + Direction::back, section->GetBlocks(), 0);

		section->CreateModel();
	}
}

void Chunk::UpdateSectionModel(glm::vec3 pos, const std::vector<std::shared_ptr<Block> >* blocks, int dirIter)
{
	int index = GetSectionIndex(GetSectionCoords(WorldToChunkCoords(pos)));

	if (m_sections.at(index) != nullptr)
	{
		m_sections.at(index)->LoadSurrounding(blocks, dirIter);
		m_sections.at(index)->CreateModel();
	}
}

glm::vec3 Chunk::GetPos() const
{
	return m_pos;
}

int Chunk::GetMaxHeight() const
{
	return m_populator.GetChunkHeight(0);
}

int Chunk::GetMinHeight() const
{
	return m_populator.GetChunkHeight(1);
}

int Chunk::GetMaxSectionHeight(glm::vec3 pos) const
{
	return m_populator.GetChunkSectionHeight(pos, 0);
}

int Chunk::GetMinSectionHeight(glm::vec3 pos) const
{
	return m_populator.GetChunkSectionHeight(pos, 1);
}

int Chunk::GetMaxBorderHeight(DirIter dirIter) const
{
	return m_populator.GetChunkBorderHeight(dirIter, 0);
}

int Chunk::GetMinBorderHeight(DirIter dirIter) const
{
	return m_populator.GetChunkBorderHeight(dirIter, 1);
}

std::shared_ptr<Block> Chunk::GetBlock(glm::vec3 pos) const
{
	glm::vec3 chunkPos = WorldToChunkCoords(pos);
	int index = GetSectionIndex(GetSectionCoords(chunkPos));
	if (m_sections.at(index) == nullptr) return nullptr;

	std::shared_ptr<Block> block = m_sections.at( GetSectionIndex( GetSectionCoords(chunkPos) ) )->GetBlock(chunkPos);
	if (block != nullptr) block->SetPos( ChunkToWorldCoords(block->GetPos()) );
	
	return block;
}

const std::vector<std::shared_ptr<Block> >* Chunk::GetSectionBlocks(glm::vec3 pos)
{
	int index = GetSectionIndex(GetSectionCoords(WorldToChunkCoords(pos)));

	if (m_sections.at(index) == nullptr) return nullptr;

	return m_sections.at( index )->GetBlocks();
}

std::vector<const std::vector<std::shared_ptr<Block> >* >  Chunk::GetBlocks() const
{
	std::vector<const std::vector<std::shared_ptr<Block> >* > blocks;

	for (auto& section : m_sections)
	{
		if (section != nullptr) blocks.push_back(section->GetBlocks());
		else blocks.push_back(nullptr);
	}

	return blocks;
}

const std::vector<std::shared_ptr<ChunkSection> > Chunk::GetSections() const
{
	return m_sections;
}

void Chunk::SetBlock(glm::vec3 pos, BlockID id)
{
	glm::vec3 chunkPos = WorldToChunkCoords(pos);
	int index = GetSectionIndex(GetSectionCoords(chunkPos));

	if (m_sections.at( index ) != nullptr) m_sections.at( index )->SetBlock(chunkPos, id);
}

bool Chunk::HasSurroundingLoadedAt(int dirIter)
{
	if (m_surroundingChunks.at(dirIter) != nullptr) return true;

	return false;
}

void Chunk::MakeSections()
{
	for (int i = 0; i < CHUNK_SIZE / SECTION_SIZE; i++)
	for (int j = 0; j < CHUNK_HEIGHT / SECTION_SIZE; j++)
	for (int k = 0; k < CHUNK_SIZE / SECTION_SIZE; k++)
	{
		std::shared_ptr<ChunkSection> temp = std::make_shared<ChunkSection>(glm::vec3(i * SECTION_SIZE, j * SECTION_SIZE, k * SECTION_SIZE));
		m_sections.push_back(temp);
	}
}

glm::vec3 Chunk::WorldToChunkCoords(glm::vec3 pos) const
{
	return pos - m_pos;
}

glm::vec3 Chunk::ChunkToWorldCoords(glm::vec3 pos) const
{
	return pos + m_pos;
}

glm::vec3 Chunk::GetSectionCoords(glm::vec3 pos) const
{
	return glm::vec3( static_cast<int>(pos.x / SECTION_SIZE) * SECTION_SIZE,
					  static_cast<int>(pos.y / SECTION_SIZE) * SECTION_SIZE, 
					  static_cast<int>(pos.z / SECTION_SIZE) * SECTION_SIZE );
}

int Chunk::GetSectionIndex(glm::vec3 pos) const
{
	if (pos.x < 0.0f) return -1;
	if (pos.y < 0.0f) return -1;
	if (pos.z < 0.0f) return -1;

	if (pos.x > (CHUNK_SIZE - SECTION_SIZE)) return -1;
	if (pos.y > (CHUNK_HEIGHT - SECTION_SIZE)) return -1;
	if (pos.z > (CHUNK_SIZE - SECTION_SIZE)) return -1;

	return (pos.x / SECTION_SIZE) * (CHUNK_SIZE / SECTION_SIZE) * (CHUNK_HEIGHT / SECTION_SIZE)
		+ (pos.y / SECTION_SIZE) * (CHUNK_SIZE / SECTION_SIZE)
		+ (pos.z / SECTION_SIZE);
}

bool Chunk::OutOfBounds(glm::vec3 pos)
{
	if (pos.x < 0.0f) return true;
	if (pos.y < 0.0f) return true;
	if (pos.z < 0.0f) return true;

	if (pos.x > (CHUNK_SIZE - 1.0f)) return true;
	if (pos.y > (CHUNK_HEIGHT - 1.0f)) return true;
	if (pos.z > (CHUNK_SIZE - 1.0f)) return true;

	return false;
}