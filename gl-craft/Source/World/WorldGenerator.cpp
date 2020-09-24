#include "WorldGenerator.hpp"

#include "WorldConstants.hpp"
#include "../Maths/Perlin.hpp"

WorldGenerator::WorldGenerator(int x, int y)
	: gridSize(CHUNK_SIZE * 2)
{
	Perlin::StartRandomization();


	// Initialize height map generation with the first grid square

	for (int i = 0; i < 2; i++)
	for (int j = 0; j < 2; j++)
	{
		m_gradients.insert(
			std::pair<Perlin::Vector2D, Perlin::Vector2D>(
				Perlin::Vector2D(i * CHUNK_SIZE, j * CHUNK_SIZE), Perlin::RandGradientVector(100)
				)
		);
	}

	std::array<Perlin::Vector2D, 4> tempGradients;

	for (int i = 0; i < 2; i++)
	for (int j = 0; j < 2; j++)
	{
		tempGradients.at(2 * i + j) = m_gradients.at(Perlin::Vector2D(i * CHUNK_SIZE, j * CHUNK_SIZE));
	}

	int biomeMultiplier = gridSize / 2;

	for (double i = 0; i < gridSize; i += 1.0)
	for (double j = 0; j < gridSize; j += 1.0)
	{
		m_heightMap.insert(
			std::pair<Perlin::Vector2D, double>(
				Perlin::Vector2D(i, j), biomeMultiplier * Perlin::CalculateNoise(
					i / static_cast<double>(gridSize),
					j / static_cast<double>(gridSize),
					tempGradients
				)
			)
		);
	}
}

void WorldGenerator::GenerateHeightMap(int x, int y)
{
}

std::map<Perlin::Vector2D, double> WorldGenerator::GetHeightMap()
{
	return m_heightMap;
}
