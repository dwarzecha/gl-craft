#include "World.hpp"

#include "WorldConstants.hpp"

World::World()
	: m_generator(0, 0)
{
	//m_generator.GenerateHeightMap();
	m_chunkManager.LoadHeightMap( m_generator.GetHeightMap() );

	for (int i = 0; i < WORLD_SIZE / CHUNK_SIZE; i++)
	for (int j = 0; j < WORLD_SIZE / CHUNK_SIZE; j++)
	{
		m_chunkManager.CreateChunk(glm::vec3(i * CHUNK_SIZE, 0.0f, j * CHUNK_SIZE));
	}
	
	//m_chunkManager.CreateChunk(glm::vec3(0.0f, 0.0f, 0.0f));

	m_chunkManager.GenModels();
}

void World::AddChunk(glm::vec3 pos)
{
	m_chunkManager.CreateChunk(pos);
}

void World::Update(glm::vec3 playerPos, float visibilityRadius)
{
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
}

void World::UpdateModel(glm::vec3 pos)
{
	m_chunkManager.UpdateModels(pos);
}

const std::vector<std::shared_ptr<Chunk> >* World::GetChunks() const
{
	return m_chunkManager.GetChunks();
}

Block World::GetBlock(glm::vec3 pos)
{
	if (OutOfBounds(pos)) return Block(BlockID::Air, glm::vec3(0.0f, 0.0f, 0.0f));
	return m_chunkManager.GetBlock(pos);
}

void World::SetBlock(glm::vec3 pos, BlockID id)
{
	m_chunkManager.SetBlock(pos, id);
}

bool World::OutOfBounds(glm::vec3 pos)
{
	if (pos.x < 0.0f) return true;
	if (pos.y < 0.0f) return true;
	if (pos.z < 0.0f) return true;

	if (pos.x > WORLD_SIZE - 1) return true;
	if (pos.y > WORLD_HEIGHT - 1) return true;
	if (pos.z > WORLD_SIZE - 1) return true;
	
	return false;

	// return m_chunkManager.OutOfBounds(pos); // causing exceptions for now
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