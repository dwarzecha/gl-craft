#ifndef PLAYINGSTATE_HPP_INCLUDED
#define PLAYINGSTATE_HPP_INCLUDED

#include <vector>

#include "GameState.hpp"
#include "StateManager.hpp"
#include "../Application.hpp"

#include "../../Renderer/RenderMaster.hpp"
#include "../../Entity/Player/Player.hpp"
#include "../../Entity/Camera/Camera.hpp"
#include "../../World/World.hpp"
#include "../../Maths/Ray.hpp"

class PlayingState : public GameState
{
public:
	void Init(StateManager* stateManager);
	void Cleanup();

	void HandleEvents(StateManager* stateManager);
	void Update(float deltaTim);
	void Draw();

	void ChangeState();

private:
	Player m_player;
	Camera m_camera;

	RenderMaster m_masterRenderer;

	World m_world;
};

#endif // PLAYINGSTATE_HPP_INCLUDED