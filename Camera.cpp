#include "Camera.hpp"

const glm::vec3 Camera::WORLD_UP{ 0.0f, 1.0f, 0.0f };

glm::mat4 Camera::GetViewMatrix() {
	auto radYaw = glm::radians(yaw);
	auto radPitch = glm::radians(pitch);

	glm::vec3 forward(
		glm::cos(radYaw) * glm::cos(radPitch),
		glm::sin(radPitch),
		glm::sin(radYaw) * glm::cos(radPitch)
	);

	forward = glm::normalize(forward);
	glm::vec3 right = glm::normalize(glm::cross(forward, WORLD_UP));
	glm::vec3 up = glm::normalize(glm::cross(right, forward));

	return glm::lookAt(position, position + forward, up);
}