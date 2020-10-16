#include "ChunkManager.hpp"



#include"WorldConstants.hpp"
#include "../Direction/Direction.hpp"
#include "Block/Block.hpp"

void ChunkManager::LoadHeightMap(std::map<Perlin::Vector2D, double> heightMap)
{
	m_heightMap = heightMap;
}

void ChunkManager::CreateChunk(glm::vec3 pos, std::mutex* mutex)
{
	std::vector<double> tempHeightMap;

	for (int i = 0; i < CHUNK_SIZE; i++)
	for (int j = 0; j < CHUNK_SIZE; j++)
	{
		tempHeightMap.push_back( m_heightMap.at( Perlin::Vector2D(pos.x + i, pos.z + j) ));
	}

	std::shared_ptr<Chunk> temp = std::make_shared<Chunk>(pos);
	temp->Populate(tempHeightMap);
	
	std::unique_lock<std::mutex> lock(*mutex);
	m_chunks.push_back(temp);
	lock.unlock();
}

void ChunkManager::GenModels()
{
	//std::lock_guard<std::mutex> guard(m_chunkMutex);
	for (auto chunk : m_chunks)
	{
		int surroundingChunksCounter = 0;

		if (!chunk->hasModel)
		{
			for (int i = 0; i < 6; i++)
			{
				int secondChunkIndex = GetChunkIndex(chunk->GetPos() + Direction::directions.at(i) * static_cast<float>(CHUNK_SIZE));

				if (secondChunkIndex != -1)
				{
					std::shared_ptr<Chunk> adjacentChunk = m_chunks.at(secondChunkIndex);

					if (!chunk->HasSurroundingLoadedAt(i)) chunk->LoadSurrounding(adjacentChunk, i);
					if (!adjacentChunk->HasSurroundingLoadedAt(Direction::Reverse(i))) adjacentChunk->LoadSurrounding(chunk, Direction::Reverse(i));
					surroundingChunksCounter++;
				}
				else
				{
					chunk->LoadSurrounding(nullptr, i);
				}
			}

			if (surroundingChunksCounter == 4)
				chunk->CreateModel(/*surroundingChunks*/);
		}
	}
}

void ChunkManager::UpdateModels(glm::vec3 pos)
{
	glm::vec3 chunkPos = glm::vec3(static_cast<int>(pos.x) % CHUNK_SIZE, pos.y, static_cast<int>(pos.z) % CHUNK_SIZE);
	if (chunkPos.x < 0.0f) chunkPos.x += CHUNK_SIZE;
	if (chunkPos.z < 0.0f) chunkPos.z += CHUNK_SIZE;

	glm::vec3 chunkCoords = GetChunkCoords(pos);
	/*
	for (int i = 0; i < SECTION_SIZE; i++)
	for (int j = 0; j < SECTION_SIZE; j++)
	{
		if (pos.y < 64 + m_heightMap.at(Perlin::Vector2D(pos.x, pos.z)) && static_cast<int>(pos.y) % SECTION_SIZE == 0)
		{
			m_chunks.at(GetChunkIndex(chunkCoords))->PopulateSection(glm::vec3(pos.x, pos.y - 1, pos.z));
		}
	}
	*/
	if (chunkPos.x == 0.0f/* && pos.x != 0.0f*/)
	{
		int index = GetChunkIndex(GetChunkCoords(pos + Direction::left));

		if (index != -1)
			m_chunks.at(index)->UpdateSectionModel(pos + Direction::left, m_chunks.at(GetChunkIndex(chunkCoords))->GetSection(pos), 3);
	}

	if (chunkPos.z == 0.0f/* && pos.z != 0.0f*/)
	{
		int index = GetChunkIndex(GetChunkCoords(pos + Direction::front));

		if (index != -1)
			m_chunks.at(index)->UpdateSectionModel(pos + Direction::front, m_chunks.at(GetChunkIndex(chunkCoords))->GetSection(pos), 1);
	}

	if (chunkPos.x == CHUNK_SIZE - 1/* && pos.x != WORLD_SIZE - 1*/)
	{
		int index = GetChunkIndex(GetChunkCoords(pos + Direction::right));

		if (index != -1)
			m_chunks.at(index)->UpdateSectionModel(pos + Direction::right, m_chunks.at(GetChunkIndex(chunkCoords))->GetSection(pos), 2);
	}

	if (chunkPos.z == CHUNK_SIZE - 1/* && pos.z != WORLD_SIZE - 1*/)
	{
		int index = GetChunkIndex(GetChunkCoords(pos + Direction::back));

		if (index != -1)
			m_chunks.at(index)->UpdateSectionModel(pos + Direction::back, m_chunks.at(GetChunkIndex(chunkCoords))->GetSection(pos), 0);
	}

	m_chunks.at( GetChunkIndex( GetChunkCoords(pos) ) )->UpdateModel(pos);
}

std::shared_ptr<Block> ChunkManager::GetBlock(glm::vec3 pos)
{
	return m_chunks.at( GetChunkIndex( GetChunkCoords(pos) ) )->GetBlock(pos);
}

const std::vector<std::shared_ptr<Chunk> >* ChunkManager::GetChunks()
{
	//std::lock_guard<std::mutex> guard(m_chunkMutex);
	return &m_chunks;
}

void ChunkManager::SetBlock(glm::vec3 pos, BlockID id)
{
	int index = GetChunkIndex(GetChunkCoords(pos));
	if (index != -1) m_chunks.at( index )->SetBlock(pos, id);
}

bool ChunkManager::OutOfBounds(glm::vec3 pos)
{
	if (pos.y < 0.0f) return true;
	if (pos.y > WORLD_HEIGHT) return true;

	bool outOfBounds = true;

	if (GetChunkIndex(GetChunkCoords(pos)) != -1)
	{
		outOfBounds = false;
	}

	return outOfBounds;
}

bool ChunkManager::ChunkWasAdded()
{
	//std::unique_lock<std::mutex> lock(*mutex);
	int retVal = m_chunks.size() - m_prevChunksCount;
	m_prevChunksCount = m_chunks.size();
	//lock.unlock();

	return retVal;
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
	if (pos.x < 0.0f) pos.x -= (CHUNK_SIZE - 1);
	if (pos.z < 0.0f) pos.z -= (CHUNK_SIZE - 1);
	
	return glm::vec3( static_cast<int>(pos.x / CHUNK_SIZE)
					  * CHUNK_SIZE, 0.0f, static_cast<int>(pos.z / CHUNK_SIZE)
					  * CHUNK_SIZE );
}

inline int ChunkManager::ZeroStepFunc(int num)
{
	if (num <= 0) return 0;
	else return num;
}