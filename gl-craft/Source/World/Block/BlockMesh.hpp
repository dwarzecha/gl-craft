#ifndef BLOCKMESH_HPP_INCLUDED
#define BLOCKMESH_HPP_INCLUDED

#include <vector>

#include "glm/glm.hpp"

namespace BlockMesh
{
	std::vector<float> Move(const std::vector<float>& vec, glm::vec3 pos);

	extern std::vector<float> top;
	extern std::vector<float> bottom;
	extern std::vector<float> left;
	extern std::vector<float> right;
	extern std::vector<float> front;
	extern std::vector<float> back;

	extern std::vector<float> texCoords;
	extern std::vector<unsigned int> indices;

	extern std::vector<std::vector<float>> faces;
}

#endif // BLOCKMESH_HPP_INCLUDED
