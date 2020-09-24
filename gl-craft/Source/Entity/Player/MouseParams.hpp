#ifndef MOUSEPARAMS_HPP_INCLUDED
#define MOUSEPARAMS_HPP_INCLUDED

#include "SFML/Window.hpp"

enum class Button
{
	None = -1,
	Left = 0,
	Right = 1
};

class MouseParams
{
public:
	MouseParams()
		: wasPressed(Button::None)
	{
	}

	bool wasClicked(sf::Mouse::Button button)
	{
		if (sf::Mouse::isButtonPressed(button))
		{
			wasPressed = static_cast<Button>(sf::Mouse::Left);
		}

		if (wasPressed == static_cast<Button>(button) && !sf::Mouse::isButtonPressed(button))
		{
			wasPressed = Button::None;
			return true;
		}

		return false;
	}

	sf::Vector2i pos;

	float sensitivity;

	int posX, posY;
	int lastX, lastY;

	float pitch, yaw;

private:
	Button wasPressed;
};

#endif // MOUSEPARAMS_HPP_INCLUDED
