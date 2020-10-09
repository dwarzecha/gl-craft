#include "Perlin.hpp"

#include <ctime>
#include <cmath>

namespace Perlin
{
	void StartRandomization()
	{
		srand(time(NULL));
	}

    double Lerp(double val1, double val2, double weight)
    {
        return (1.0 - weight) * val1 + weight * val2;
    }

    Vector2D RandGradientVector(int precision)
    {
        Vector2D grad;

        grad.x = rand() % (precision * 2 + 1);
        grad.y = rand() % (precision * 2 + 1);

        if (grad.x > precision)
            grad.x = ((precision * 2 + 1) - grad.x) * -1.0;

        if (grad.y > precision)
            grad.y = ((precision * 2 + 1) - grad.y) * -1.0;           

        double length = sqrt(grad.x * grad.x + grad.y * grad.y);

        Vector2D unitGrad;
        
		unitGrad.x = grad.x / length;
		unitGrad.y = grad.y / length;

        return unitGrad;
    }

    double DotProduct(Vector2D vec1, Vector2D vec2)
    {
        return vec1.x * vec2.x + vec1.y * vec2.y;
    }

    double CalculateNoise(double x, double y, std::array<Vector2D, 4> gradients)
    {
        // Determine grid cell coordinates

        std::array<Vector2D, 4> gridCoords;

        gridCoords.at(0).x = static_cast<int>(x);
        gridCoords.at(0).y = static_cast<int>(y);

        gridCoords.at(1).x = gridCoords.at(0).x;
        gridCoords.at(1).y = gridCoords.at(0).y + 1;

        gridCoords.at(2).x = gridCoords.at(0).x + 1;
        gridCoords.at(2).y = gridCoords.at(0).y;

        gridCoords.at(3).x = gridCoords.at(0).x + 1;
        gridCoords.at(3).y = gridCoords.at(0).y + 1;

        std::array<Vector2D, 4> distances;

        for (int i = 0; i < 4; i++)
        {
            distances.at(i).x = x - gridCoords.at(i).x;
            distances.at(i).y = y - gridCoords.at(i).y;
        }

        std::array<double, 4> values;

        for (int i = 0; i < 4; i++)
        {
            values.at(i) = DotProduct(gradients.at(i), distances.at(i));
        }

        double lerpVal1 = Lerp(values.at(0), values.at(2), x - static_cast<int>(x));
        double lerpVal2 = Lerp(values.at(1), values.at(3), x - static_cast<int>(x));
        
		double retVal = Lerp(lerpVal1, lerpVal2, y - static_cast<int>(y));

        return retVal;
    }
}
