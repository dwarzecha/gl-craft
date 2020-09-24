#include "BlockMesh.hpp"

namespace BlockMesh
{
	std::vector<float> Move(const std::vector<float>& vec, glm::vec3 pos)
	{
		std::vector <float> temp;

		for (int i = 0; i < vec.size(); i++)
		{
			temp.push_back(pos.x + vec.at(i++));
			temp.push_back(pos.y + vec.at(i++));
			temp.push_back(pos.z + vec.at(i));
		}

		return temp;
	}

	std::vector<float> front = {
		 0.0f,  1.0f,  0.0f,
		 0.0f,  0.0f,  0.0f,
		 1.0f,  1.0f,  0.0f,
		 1.0f,  0.0f,  0.0f
	};

	std::vector<float> back = {
		 0.0f,  1.0f,  1.0f,
		 0.0f,  0.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  0.0f,  1.0f
	};

	std::vector<float> left = {
		 0.0f,  1.0f,  0.0f,
		 0.0f,  0.0f,  0.0f,
		 0.0f,  1.0f,  1.0f,
		 0.0f,  0.0f,  1.0f
	};

	std::vector<float> right = {
		 1.0f,  1.0f,  0.0f,
		 1.0f,  0.0f,  0.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  0.0f,  1.0f
	};

	std::vector<float> top = {
		 0.0f,  1.0f,  0.0f,
		 0.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  0.0f,
		 1.0f,  1.0f,  1.0f
	};

	std::vector<float> bottom = {
		 0.0f,  0.0f,  0.0f,
		 0.0f,  0.0f,  1.0f,
		 1.0f,  0.0f,  0.0f,
		 1.0f,  0.0f,  1.0f
	};

	std::vector<float> texCoords = {
		 0.0f,  0.0f,
		 0.0f,  1.0f,
		 1.0f,  0.0f,
		 1.0f,  1.0f
	};

	std::vector<unsigned int> indices = {
		 0, 1, 2,
		 1, 2, 3
	};

	std::vector<std::vector<float> > faces = { front, back, left, right, top, bottom };
}
