#ifndef DIRECTION_HPP_INCLUDED
#define DIRECTION_HPP_INCLUDED

#include <vector>

#include "glm/glm.hpp"

namespace Direction
{
	extern glm::vec3 front;
	extern glm::vec3 back;
	extern glm::vec3 left;
	extern glm::vec3 right;
	extern glm::vec3 up;
	extern glm::vec3 down;

	extern std::vector<glm::vec3> directions;
};

#endif // DIRECTION_HPP_INCLUDED

