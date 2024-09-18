#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
	static const glm::vec3 WORLD_UP;

	glm::vec3 position{};
	float fov = 60.0f;
	float yaw = -90.0f;
	float pitch = 0.0f;

	Camera(glm::vec3 position, float yaw = -90.0f, float pitch = 0.0f, float fov = 60.0f)
		: position(position), yaw(yaw), pitch(pitch), fov(fov) {}
	
	glm::mat4 GetProjectionMatrix(float width, float height) {
		return glm::perspective(glm::radians(fov), width / height, 0.1f, 100.0f);
	}
	
	glm::mat4 GetViewMatrix();

private: 
};