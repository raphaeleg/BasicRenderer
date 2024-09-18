#include "Camera.hpp"

const glm::vec3 Camera::WORLD_UP{ 0.0f, 1.0f, 0.0f };

void Camera::UpdateDirectionVectors() {
	auto radYaw = glm::radians(yaw);
	auto radPitch = glm::radians(pitch);

	forward = glm::normalize(glm::vec3(
		glm::cos(radYaw) * glm::cos(radPitch),
		glm::sin(radPitch),
		glm::sin(radYaw) * glm::cos(radPitch)
	));
	right = glm::normalize(glm::cross(forward, WORLD_UP));
	up = glm::normalize(glm::cross(right, forward));
}