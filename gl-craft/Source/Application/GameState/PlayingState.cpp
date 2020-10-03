#include "PlayingState.hpp"

#include <iostream>

#include "../../World/WorldConstants.hpp"

void PlayingState::Init(StateManager* stateManager)
{
	
	m_camera.Init(&m_player, *stateManager->pApplication->GetConfig());
	m_player.Init(*stateManager->pApplication->GetConfig());
	m_masterRenderer.Init(&m_camera);

	//stateManager->pApplication->GetContext()->window.setActive(false);
	// m_world.GenChunks(&stateManager->pApplication->GetContext()->window);

	chunkThread = std::make_unique<std::thread>(&World::GenChunks, &m_world, &chunkMutex);
	//chunkThread->join();
	

	//stateManager->pApplication->GetContext()->window.setActive(true);
}

void PlayingState::Cleanup()
{
	
}

void PlayingState::HandleEvents(StateManager* stateManager)
{
	m_player.HandleEvents(stateManager->pApplication->GetContext()->window);
}

void PlayingState::Update(float deltaTime)
{
	std::unique_lock<std::mutex> lock(chunkMutex);
	m_world.Update();
	lock.unlock();

	m_player.Update(deltaTime);
	m_camera.Update();

	if (m_player.GetRayCast())
	{
		for ( Ray ray(m_player.direction, m_player.position);
			  ray.GetLength() < 6.0f;
			  ray.Update(0.1f) )
		{
			float rEndPosX = ray.GetEndPos().x;
			float rEndPosZ = ray.GetEndPos().z;

			if (rEndPosX < 0.0f) rEndPosX -= 1.0f;
			if (rEndPosZ < 0.0f) rEndPosZ -= 1.0f;

			glm::vec3 pos( static_cast<int>(rEndPosX),
						   static_cast<int>(ray.GetEndPos().y),
				           static_cast<int>(rEndPosZ) );


			std::shared_ptr<Block> b = m_world.GetBlock(pos);
			if (b != nullptr && b->GetID() != BlockID::Air)
			{
				m_world.SetBlock(pos, BlockID::Air);
				m_world.UpdateModel(pos);

				break;
			}
		}
	}

	lock.lock();
	//if (m_world.ChunkWasAdded())
	for (auto chunk : *m_world.GetChunks())
	{
		float viewDistance = 4 * CHUNK_SIZE * 1.41f;

		if (chunk->hasModel)// && abs(chunk->GetPos().x - m_player.position.x) < viewDistance && abs(chunk->GetPos().z - m_player.position.z) < viewDistance)
			m_masterRenderer.AddQuad(chunk);
	}
	lock.unlock();

	std::cout << m_player.direction.x << " " << m_player.direction.z << "\n";
}

void PlayingState::Draw()
{
	m_masterRenderer.FinishRender();
}

void PlayingState::ChangeState()
{

}