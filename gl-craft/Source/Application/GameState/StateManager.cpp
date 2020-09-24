#include "StateManager.hpp"

#include "../../Config/Config.hpp"

void StateManager::PushState(std::unique_ptr<GameState> state)
{
	m_states.push_back(std::move(state));
	m_states.back()->Init(this);
}

void StateManager::PopState()
{
	m_states.pop_back();
}

void StateManager::HandleEvents()
{
	m_states.back()->HandleEvents(this);
}

void StateManager::Update(float deltaTime)
{
	m_states.back()->Update(deltaTime);
}

void StateManager::Draw()
{
	m_states.back()->Draw();
}