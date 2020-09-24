#ifndef MESH_HPP_INCLUDED
#define MESH_HPP_INCLUDED

#include <vector>

struct Mesh
{
	std::vector<float> vertices;
	std::vector<float> texCoords;
	std::vector<unsigned int> indices;
};

#endif // MESH_HPP_INCLUDED
