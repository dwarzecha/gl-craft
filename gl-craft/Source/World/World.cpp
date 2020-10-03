#include "World.hpp"

#include <iostream>

#include "WorldConstants.hpp"

World::World()
	: m_generator(0, 0)
{
}

void World::GenChunks(std::mutex* mutex)
{
	//window->setActive(true);

	int worldSize = 64;

	m_chunkManager.LoadHeightMap(m_generator.GetHeightMap());

	for (int i = -worldSize / CHUNK_SIZE; i < worldSize / CHUNK_SIZE; i++)
	for (int j = -worldSize / CHUNK_SIZE; j < worldSize / CHUNK_SIZE; j++)
	{
		auto map = m_generator.GetHeightMap();

		if (map.find(Perlin::Vector2D(i* CHUNK_SIZE, j * CHUNK_SIZE)) == map.end())
		{
			int x = i * CHUNK_SIZE;
			int y = j * CHUNK_SIZE;

			if (x % m_generator.GetGridSize())
			{
				if (x > 0) x += (m_generator.GetGridSize() - x % m_generator.GetGridSize());
				if (x < 0) x -= (m_generator.GetGridSize() + x % m_generator.GetGridSize());
			}

			if (y % m_generator.GetGridSize())
			{
				if (y > 0) y += (m_generator.GetGridSize() - y % m_generator.GetGridSize());
				if (y < 0) y -= (m_generator.GetGridSize() + y % m_generator.GetGridSize());
			}

			m_generator.GenerateHeightMap(x, y);
			m_chunkManager.LoadHeightMap(m_generator.GetHeightMap());
		}

		m_chunkManager.CreateChunk(glm::vec3(i * CHUNK_SIZE, 0.0f, j * CHUNK_SIZE), mutex);
	}

	//window->setActive(false);
}

void World::GenModels()
{
	
}

/*
void World::AddChunk(glm::vec3 pos)
{
	m_chunkManager.CreateChunk(pos);
}
*/

void World::Update(/*glm::vec3 playerPos, float visibilityRadius*/)
{
	/*
	glm::vec3 chunkPos = glm::vec3(playerPos.x, 0.0f, playerPos.z);

	for (int i = 0; i < visibilityRadius; i += CHUNK_SIZE)
	{
		if (!ChunkExists(chunkPos))
			m_chunkManager.CreateChunk(chunkPos);
		// m_chunkManager.UpdateChunk(chunkPos);
		chunkPos.z += i;
		if (!ChunkExists(chunkPos))
			m_chunkManager.CreateChunk(chunkPos);
		// m_chunkManager.UpdateChunk(chunkPos);
		chunkPos.x += i;
	}
	*/
	//std::cout << m_chunkManager.ChunkWasAdded();
	if (m_chunkManager.ChunkWasAdded())
		m_chunkManager.GenModels();
}

void World::UpdateModel(glm::vec3 pos)
{
	m_chunkManager.UpdateModels(pos);
}

const std::vector<std::shared_ptr<Chunk> >* World::GetChunks()
{
	return m_chunkManager.GetChunks();
}

std::shared_ptr<Block> World::GetBlock(glm::vec3 pos)
{
	if (OutOfBounds(pos)) return nullptr;
	return m_chunkManager.GetBlock(pos);
}

void World::SetBlock(glm::vec3 pos, BlockID id)
{
	m_chunkManager.SetBlock(pos, id);
}
/*
bool World::ChunkWasAdded()
{
	return m_chunkManager.ChunkWasAdded();
}
*/
bool World::OutOfBounds(glm::vec3 pos)
{
	return m_chunkManager.OutOfBounds(pos);
}

bool World::ChunkExists(glm::vec3 pos)
{
	for (auto chunk : *m_chunkManager.GetChunks())
	{
		if (chunk->GetPos() == pos)
		{
			return true;
		}
	}

	return false;
}