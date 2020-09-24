#ifndef MATRIX_HPP_INCLUDED
#define MATRIX_HPP_INCLUDED

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "../Config/Config.hpp"
#include "../Entity/Entity.hpp"

glm::mat4 MakeProjectionMatrix(const Config& config);
glm::mat4 MakeViewMatrix(const Entity& entity);

#endif // MATRIX_HPP_INCLUDED
