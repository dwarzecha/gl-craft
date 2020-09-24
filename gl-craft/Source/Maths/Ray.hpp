#ifndef RAY_HPP_INCLUDED
#define RAY_HPP_INCLUDED

#include "glm/glm.hpp"

class Ray
{
public:
	Ray(glm::vec3 direction, glm::vec3 startPos);

	void Update(float step);

	glm::vec3 GetEndPos() const;
	const float GetLength() const;

private:
	glm::vec3 m_direction;
	glm::vec3 m_startPos;
	glm::vec3 m_endPos;
};

#endif // RAY_HPP_INCLUDED