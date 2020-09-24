#include "Matrix.hpp"

#include "../Direction/Direction.hpp"

glm::mat4 MakeProjectionMatrix(const Config& config)
{
	return glm::perspective( glm::radians(config.fieldOfView),
							 (float) config.windowSizeX / (float) config.windowSizeY,
							 1.0f,
							 (float) config.viewDistance );
}

glm::mat4 MakeViewMatrix(const Entity& entity)
{
	return glm::lookAt( entity.position,
						entity.position + entity.direction,
						Direction::up );
}