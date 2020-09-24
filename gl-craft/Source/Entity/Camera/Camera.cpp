#include "Camera.hpp"

Camera::Camera()
{
	position = glm::vec3(0.0, 0.0, 3.0);
}

void Camera::Init(Entity* entity, const Config& config)
{		
	m_projectionMatrix = MakeProjectionMatrix(config);
	position = glm::vec3(0.0, 0.0, 3.0);
	HookEntity(entity);
}

void Camera::HookEntity(Entity* entity)
{
	m_Entity = entity;
}

void Camera::LoadConfig(const Config& config)
{
	m_projectionMatrix = MakeProjectionMatrix(config);
}

void Camera::Update()
{
	position = m_Entity->position;
	direction = m_Entity->direction;

	m_viewMatrix = MakeViewMatrix(*m_Entity);
}

glm::mat4 Camera::GetProjectionMatrix() const
{
	return m_projectionMatrix;
}

glm::mat4 Camera::GetViewMatrix() const
{
	return m_viewMatrix;
}