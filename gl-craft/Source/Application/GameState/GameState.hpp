#ifndef GAMESTATE_HPP_INCLUDED
#define GAMESTATE_HPP_INCLUDED

#include "../../Util/NonCopyable.hpp"

class StateManager;

struct GameState :  public NonCopyable
{
	virtual void Init(StateManager* stateManager) = 0;
	virtual void Cleanup() = 0;

	virtual void HandleEvents(StateManager* stateManager) = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;

	virtual void ChangeState() = 0;
};

#endif // GAMESTATE_HPP_INCLUDED
