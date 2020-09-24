#include "Ray.hpp"

Ray::Ray(glm::vec3 direction, glm::vec3 startPos)
	:  m_direction(direction), m_startPos(startPos), m_endPos(startPos)
{
}

void Ray::Update(float step)
{
	m_endPos += m_direction * step;
}

glm::vec3 Ray::GetEndPos() const
{
	return m_endPos;
}

const float Ray::GetLength() const
{
	return glm::length(m_endPos - m_startPos);
}