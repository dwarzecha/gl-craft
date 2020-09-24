#ifndef APPLICATION_HPP_INCLUDED
#define APPLICATION_HPP_INCLUDED

#include <vector>
#include <string>

#include "GameState/GameState.hpp"
#include "Context/Context.hpp"
#include "GameState/StateManager.hpp"
#include "../Config/Config.hpp"

class Application
{
public:
	Application(std::string name);

	void RunLoop();

	const Context* GetContext() const;
	const Config* GetConfig() const;

private:
	void Init();
	void HandleEvents();

	Context m_context;
	StateManager m_stateManager;
	Config m_config;

	bool m_running;
};

#endif // APPLICATION_HPP_INCLUDED