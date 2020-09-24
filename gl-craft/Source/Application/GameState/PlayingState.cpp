#include "PlayingState.hpp"

#include <iostream>

#include "../../World/WorldConstants.hpp"

void PlayingState::Init(StateManager* stateManager)
{
	m_camera.Init(&m_player, *stateManager->pApplication->GetConfig());
	m_player.Init(*stateManager->pApplication->GetConfig());
	m_masterRenderer.Init(&m_camera);
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
	m_player.Update(deltaTime);
	m_camera.Update();

	if (m_player.GetRayCast())
	{
		for ( Ray ray(m_player.direction, m_player.position);
			  ray.GetLength() < 6.0f;
			  ray.Update(0.1f) )
		{
			glm::vec3 pos( static_cast<int>(ray.GetEndPos().x),
						   static_cast<int>(ray.GetEndPos().y),
				           static_cast<int>(ray.GetEndPos().z) );

			if (m_world.GetBlock(pos).GetID() != BlockID::Air)
			{
				m_world.SetBlock(pos, BlockID::Air);
				m_world.UpdateModel(pos);

				break;
			}
		}
	}

	for (auto chunk : *m_world.GetChunks())
	{
		// if (abs(chunk->GetPos().x - m_player.position.x) < 2 * CHUNK_SIZE && abs(chunk->GetPos().z - m_player.position.z) < 2 * CHUNK_SIZE)
			m_masterRenderer.AddQuad(chunk);
	}
}

void PlayingState::Draw()
{
	m_masterRenderer.FinishRender();
}

void PlayingState::ChangeState()
{

}