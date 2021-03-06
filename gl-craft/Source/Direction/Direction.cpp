#include "Direction.hpp"

namespace Direction
{
	glm::vec3 front(0.0f, 0.0f, -1.0f);
	glm::vec3 back(0.0f, 0.0f, 1.0f);
	glm::vec3 left(-1.0f, 0.0f, 0.0f);
	glm::vec3 right(1.0f, 0.0f, 0.0f);
	glm::vec3 up(0.0f, 1.0f, 0.0f);
	glm::vec3 down(0.0f, -1.0f, 0.0f);

	std::vector<glm::vec3> directions = { front, back, left, right, up, down };

	int Reverse(int i)
	{
		switch (i)
		{
		case 0:
			return 1;
		case 1:
			return 0;
		case 2:
			return 3;
		case 3:
			return 2;
		case 4:
			return 5;
		case 5:
			return 4;

		default:
			return -1;
		}
	}
}