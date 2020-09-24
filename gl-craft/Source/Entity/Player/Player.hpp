#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include "SFML/Window.hpp"
#include "glm/glm.hpp"

#include "../../Controls/Controls.hpp"
#include "../Camera/Camera.hpp"
#include "../../Config/Config.hpp"
#include "MouseParams.hpp"

class Player : public Entity
{
public:
	Player();
	void Init(const Config& config);
    
	void Update(float deltaTime);
	void HandleEvents(const sf::Window& window);
	void LoadConfig(const Config& config);

	bool GetRayCast() const;
    
private:
	void ProcessKeyboardInput();
	void ProcessMouseInput(const sf::Window& window);

	MouseParams m_mp;
	bool m_rayCast;

    float m_speed;
};

#endif // PLAYER_HPP_INCLUDED
