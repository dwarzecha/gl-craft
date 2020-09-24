#include "ChunkManager.hpp"

#include"WorldConstants.hpp"
#include "../Direction/Direction.hpp"
#include "Block/Block.hpp"

void ChunkManager::LoadHeightMap(std::map<Perlin::Vector2D, double> heightMap)
{
	m_heightMap = heightMap;
}

void ChunkManager::CreateChunk(glm::vec3 pos)
{
	std::vector<double> tempHeightMap;

	for (int i = 0; i < CHUNK_SIZE; i++)
	for (int j = 0; j < CHUNK_SIZE; j++)
	{
		tempHeightMap.push_back( m_heightMap.at( Perlin::Vector2D(pos.x + i, pos.z + j) ));
	}

	std::shared_ptr<Chunk> temp = std::make_shared<Chunk>(pos);
	temp->Populate(tempHeightMap);

	m_chunks.push_back(temp);
}

void ChunkManager::GenModels()
{
	for (auto chunk : m_chunks)
	{
		for (int i = 0; i < 6; i++)
		{
			std::vector<std::shared_ptr<ChunkSection> > adjacentChunkSections;

			for (int i = 0; i < (CHUNK_HEIGHT * CHUNK_SIZE * CHUNK_SIZE) / (SECTION_SIZE * SECTION_SIZE * SECTION_SIZE); i++)
			{
				adjacentChunkSections.push_back(nullptr);
			}

			int secondChunkIndex = GetChunkIndex(chunk->GetPos() + Direction::directions.at(i) * static_cast<float>(CHUNK_SIZE));

			if (secondChunkIndex != -1)
				adjacentChunkSections = m_chunks.at(secondChunkIndex)->GetSections();

			chunk->LoadSurrounding(adjacentChunkSections, i);
		}
		
		chunk->CreateModel();
	}
}

void ChunkManager::UpdateModels(glm::vec3 pos)
{
	glm::vec3 chunkPos = glm::vec3(static_cast<int>(pos.x) % CHUNK_SIZE, pos.y, static_cast<int>(pos.z) % CHUNK_SIZE);
	glm::vec3 chunkCoords = GetChunkCoords(pos);

	if (chunkPos.x == 0.0f/* && pos.x != 0.0f*/)
	{
		int index = GetChunkIndex(GetChunkCoords(pos + Direction::left));

		if (index != -1)
			m_chunks.at(index)->UpdateSectionModel(pos + Direction::left, m_chunks.at(GetChunkIndex(chunkCoords))->GetSectionBlocks(pos), 3);
	}

	if (chunkPos.z == 0.0f/* && pos.z != 0.0f*/)
	{
		int index = GetChunkIndex(GetChunkCoords(pos + Direction::front));

		if (index != -1)
			m_chunks.at(index)->UpdateSectionModel(pos + Direction::front, m_chunks.at(GetChunkIndex(chunkCoords))->GetSectionBlocks(pos), 1);
	}

	if (chunkPos.x == CHUNK_SIZE - 1/* && pos.x != WORLD_SIZE - 1*/)
	{
		int index = GetChunkIndex(GetChunkCoords(pos + Direction::right));

		if (index != -1)
			m_chunks.at(index)->UpdateSectionModel(pos + Direction::right, m_chunks.at(GetChunkIndex(chunkCoords))->GetSectionBlocks(pos), 2);
	}

	if (chunkPos.z == CHUNK_SIZE - 1/* && pos.z != WORLD_SIZE - 1*/)
	{
		int index = GetChunkIndex(GetChunkCoords(pos + Direction::back));

		if (index != -1)
			m_chunks.at(index)->UpdateSectionModel(pos + Direction::back, m_chunks.at(GetChunkIndex(chunkCoords))->GetSectionBlocks(pos), 0);
	}

	m_chunks.at( GetChunkIndex( GetChunkCoords(pos) ) )->UpdateModel(pos);
}

Block ChunkManager::GetBlock(glm::vec3 pos)
{
	return m_chunks.at( GetChunkIndex( GetChunkCoords(pos) ) )->GetBlock(pos);
}

const std::vector<std::shared_ptr<Chunk> >* ChunkManager::GetChunks() const
{
	return &m_chunks;
}

void ChunkManager::SetBlock(glm::vec3 pos, BlockID id)
{
	m_chunks.at( GetChunkIndex( GetChunkCoords(pos) ) )->SetBlock(pos, id);
}

bool ChunkManager::OutOfBounds(glm::vec3 pos)
{
	bool outOfBounds = true;

	if (GetChunkIndex(GetChunkCoords(pos)) != -1)
	{
		outOfBounds = false;
	}

	return outOfBounds;
}

int ChunkManager::GetChunkIndex(glm::vec3 pos) const
{
	for (int i = 0; i < m_chunks.size(); i++)
	{
		if (m_chunks.at(i)->GetPos() == pos)
		{
			return i;
		}
	}

	return -1;

	/*
	if (pos.x < 0.0f) return -1;
	if (pos.z < 0.0f) return -1;

	if (pos.x > WORLD_SIZE - CHUNK_SIZE) return -1;
	if (pos.z > WORLD_SIZE - CHUNK_SIZE) return -1;

	return (pos.x / CHUNK_SIZE) * (WORLD_SIZE / CHUNK_SIZE) + (pos.z / CHUNK_SIZE);
	*/
}

glm::vec3 ChunkManager::GetChunkCoords(glm::vec3 pos) const
{
	return glm::vec3( static_cast<int>(pos.x / CHUNK_SIZE)
					  * CHUNK_SIZE, 0.0f, static_cast<int>(pos.z / CHUNK_SIZE)
					  * CHUNK_SIZE );
}