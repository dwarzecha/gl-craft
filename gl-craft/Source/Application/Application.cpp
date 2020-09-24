#include "Application.hpp"
#include "GameState/PlayingState.hpp"

Application::Application(std::string name)
	: m_running(true), m_context(name), m_stateManager(this)
{
	Init();
}

void Application::Init()
{
	m_config.windowSizeX = 800;
	m_config.windowSizeY = 600;

	m_config.viewDistance = 100;
	m_config.mouseSensitivity = 0.2f;

	m_config.fieldOfView = 45.0f;
}

void Application::RunLoop()
{
	sf::Clock clock;

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	std::unique_ptr<PlayingState> state = std::make_unique<PlayingState>();
	m_stateManager.PushState(std::move(state));

	while (m_running)
	{
		float currentFrame = clock.getElapsedTime().asSeconds();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		HandleEvents();
		m_stateManager.HandleEvents();
		m_stateManager.Update(deltaTime);
		m_stateManager.Draw();

		m_context.window.display();
	}

	m_context.window.close();
}

void Application::HandleEvents()
{
	sf::Event windowEvent;
	while (m_context.window.pollEvent(windowEvent))
	{
		switch (windowEvent.type)
		{
		case sf::Event::KeyPressed:
			if (windowEvent.key.code == sf::Keyboard::Escape)
			{
				m_running = false;
			}
			break;

		case sf::Event::Closed:
			m_running = false;
			break;
		}
	}
}

const Context* Application::GetContext() const
{
	return &m_context;
}

const Config* Application::GetConfig() const
{
	return &m_config;
}