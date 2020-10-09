#ifndef PERLIN_HPP_INCLUDED
#define PERLIN_HPP_INCLUDED

#include <array>
#include <tuple>

namespace Perlin
{
    struct Vector2D
	{
		Vector2D() = default;
		Vector2D(int iX, int iY) : x(iX), y(iY) {};

		bool operator<(const Vector2D& vec) const
		{
			return std::tie(x, y) < std::tie(vec.x, vec.y);
		}

		double x, y;
	};

	void StartRandomization();

    double Lerp(double val1, double val2, double weight);

    Vector2D RandGradientVector(int precision);
    double DotProduct(Vector2D vec1, Vector2D vec2);

    double CalculateNoise(double x, double y, std::array<Vector2D, 4> gradients);
}

#endif // PERLIN_HPP_INCLUDED