#ifndef WORLDGENERATOR_HPP_INCLUDED
#define WORLDGENERATOR_HPP_INCLUDED

#include <map>

#include "../Maths/Perlin.hpp"

class WorldGenerator
{
public:
	WorldGenerator(int x, int y);

	void GenerateHeightMap(int x, int y);
	std::map<Perlin::Vector2D, double> GetHeightMap();

private:
	void AddGradients();

	std::map<Perlin::Vector2D, double> m_heightMap;
	std::map<Perlin::Vector2D, Perlin::Vector2D> m_gradients;
	int gridSize;
};

#endif // WORLDGENERATOR_HPP_INCLUDED