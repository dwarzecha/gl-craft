#ifndef STATEMANAGER_HPP_INCLUDED
#define STATEMANAGER_HPP_INCLUDED

#include <vector>
#include <memory>

#include "GameState.hpp"

class Application;

class StateManager
{
public:
	StateManager(Application* app)
		: pApplication(app)
	{
	};

	void PushState(std::unique_ptr<GameState> state);
	void PopState();

	void HandleEvents();
	void Update(float deltaTime);
	void Draw();

	Application* pApplication;

private:
	std::vector<std::unique_ptr<GameState> > m_states;
};

#endif // STATEMANAGER_HPP_INCLUDED