#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SFML/System/Vector2.hpp>

class Camera {
public:
	glm::vec3 position{ 0.0f };

	Camera(glm::vec3 position, float pitch = 0.0f, float yaw = -90.0f, float fov = 60.0f)
		: position(position), pitch(pitch), yaw(yaw), fov(fov) {};

	void Update(float _deltaTime, sf::Vector2i moveDirection, sf::Vector2i mousePosition);
	
	glm::mat4 GetProjectionMatrix(float width, float height) {
		return glm::perspective(glm::radians(fov), width / height, 0.1f, 100.0f);
	}
	glm::mat4 GetProjectionMatrix(unsigned int width, unsigned int height) {
		return GetProjectionMatrix(static_cast<float>(width), static_cast<float>(height));
	}
	glm::mat4 GetViewMatrix() const { return glm::lookAt(position, position + forward, up); }

	sf::Vector2i lastMousePos{};
	
private: 
	static const glm::vec3 WORLD_UP;
	static constexpr float CAM_SPEED = 6.0f;
	static constexpr float MOUSE_SENSITIVITY = 25.0f;

	float deltaTime = 0.0f;
	float fov = 60.0f;
	float yaw = -90.0f;
	float pitch = 0.0f;
	glm::vec3 forward{ 0.0f };
	glm::vec3 right{ 0.0f };
	glm::vec3 up{ 0.0f };

	bool isRotating = false;

	void UpdateDirectionVectors();
	void UpdatePosition(sf::Vector2i moveDirection);
	void UpdateRotation(sf::Vector2i mousePosition);

	void Forward() { position += forward * (CAM_SPEED * deltaTime); }
	void Backward() { position -= forward * (CAM_SPEED * deltaTime); }
	void Left() { position += right * (CAM_SPEED * deltaTime); }
	void Right() { position -= right * (CAM_SPEED * deltaTime); }
};