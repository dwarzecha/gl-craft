#ifndef CONTROLS_HPP_INCLUDED
#define CONTROLS_HPP_INCLUDED

#include "SFML/Window.hpp"
#include "glm/glm.hpp"

class Controls
{
public:
    glm::vec3 direction;
    sf::Vector2i mousePos;
    int mousePosX, mousePosY, lastX, lastY;
    float pitch, yaw;
    float sensitivity;
};

#endif // CONTROLS_HPP_INCLUDED
