#include "Player.hpp"

#include "glm/gtc/matrix_transform.hpp"

#include "../../Direction/Direction.hpp"

Player::Player()
	: m_rayCast(false)
{
	position = glm::vec3(0.0, 64.0, 3.0);
	direction = glm::vec3(0.0f, 0.0f, -1.0f);

	m_mp.posX = 0;
	m_mp.posY = 0;
	m_mp.lastX = 400;
	m_mp.lastY = 300;
	m_mp.pitch = 0.0f;
	m_mp.yaw = -90.0f;

	sf::Mouse::setPosition(sf::Vector2i(400, 300));
}

void Player::Init(const Config& config)
{
	m_mp.sensitivity = config.mouseSensitivity;
}

void Player::Update(float deltaTime)
{
	m_speed = deltaTime * 15.0f;
}

void Player::HandleEvents(const sf::Window& window)
{
	ProcessKeyboardInput();
	ProcessMouseInput(window);
}

void Player::LoadConfig(const Config& config)
{
	m_mp.sensitivity = config.mouseSensitivity;
}

bool Player::GetRayCast() const
{
	return m_rayCast;
}

void Player::ProcessKeyboardInput()
{   
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        position += m_speed * direction;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        position -= m_speed * direction;
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        position -= m_speed * glm::normalize(glm::cross(direction, Direction::up));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        position += m_speed * glm::normalize(glm::cross(direction, Direction::up));
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        position += m_speed * Direction::up;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        position -= m_speed * Direction::up;
    }
}

void Player::ProcessMouseInput(const sf::Window& window)
{
	// Mouse movement

    m_mp.pos = sf::Mouse::getPosition(window);
    
    float xOffset = (m_mp.pos.x + m_mp.posX) - m_mp.lastX;
    float yOffset = m_mp.lastY - (m_mp.pos.y + m_mp.posY);
    
    xOffset *= m_mp.sensitivity;
    yOffset *= m_mp.sensitivity;
    
    m_mp.yaw += xOffset;

	if (m_mp.yaw > 359.0f)
		m_mp.posX %= 799;
	if (m_mp.yaw < -359.0f)
		m_mp.posX %= 799;

	m_mp.lastX = (m_mp.pos.x + m_mp.posX);
	m_mp.lastY = (m_mp.pos.y + m_mp.posY);

    m_mp.pitch += yOffset;
    
    if (m_mp.pitch > 89.0f)
		m_mp.pitch = 89.0f;
    if (m_mp.pitch < -89.0f)
		m_mp.pitch = -89.0f;
    
    direction.x = cos(glm::radians(m_mp.yaw)) * cos(glm::radians(m_mp.pitch));
    direction.z = sin(glm::radians(m_mp.yaw)) * cos(glm::radians(m_mp.pitch));
    direction.y = sin(glm::radians(m_mp.pitch));
    
    direction = glm::normalize(direction);
    
    if (m_mp.pos.x == 799)
    {
		m_mp.posX += 799;
        sf::Mouse::setPosition(sf::Vector2i(1, m_mp.pos.y), window);
    }
    else if (m_mp.pos.x == 0)
    {
		m_mp.posX -= 799;
        sf::Mouse::setPosition(sf::Vector2i(798, m_mp.pos.y), window);
    }
    
    if (m_mp.pos.y == 599)
    {
		m_mp.posY += 599;
        sf::Mouse::setPosition(sf::Vector2i(m_mp.pos.x, 1), window);
    }
    else if (m_mp.pos.y == 0)
    {
		m_mp.posY -= 599;
        sf::Mouse::setPosition(sf::Vector2i(m_mp.pos.x, 598), window);
    }

	// Mouse buttons

	if (m_mp.wasClicked(sf::Mouse::Left))
	{
		m_rayCast = true;
	}
	else
	{
		m_rayCast = false;
	}
}
