#ifndef CAMERA_HPP_INCLUDED
#define CAMERA_HPP_INCLUDED

#include <memory>

#include "SFML/Window.hpp"
#include "glm/glm.hpp"

#include "../../Shader/Shader.hpp"
#include "../Entity.hpp"
#include "../../Maths/Matrix.hpp"

class Camera : public Entity
{
public:
	Camera();
    void Init(Entity* entity, const Config& config);

	void HookEntity(Entity* entity);
	void LoadConfig(const Config& config);

	void Update();

	glm::mat4 GetProjectionMatrix() const;
	glm::mat4 GetViewMatrix() const;
    
private:
	Entity* m_Entity;

	glm::mat4 m_projectionMatrix;
	glm::mat4 m_viewMatrix;
};

#endif // CAMERA_HPP_INCLUDED
