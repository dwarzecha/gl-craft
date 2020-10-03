#ifndef DIRECTION_HPP_INCLUDED
#define DIRECTION_HPP_INCLUDED

#include <vector>

#include "glm/glm.hpp"

enum class DirIter
{
	Front = 0,
	Back = 1,
	Left = 2,
	Right = 3,
	Up = 4,
	Down = 5
};

namespace Direction
{
	extern glm::vec3 front;
	extern glm::vec3 back;
	extern glm::vec3 left;
	extern glm::vec3 right;
	extern glm::vec3 up;
	extern glm::vec3 down;

	extern std::vector<glm::vec3> directions;

	int Reverse(int i);
};

#endif // DIRECTION_HPP_INCLUDED

