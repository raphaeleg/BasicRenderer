#include "Camera.hpp"
#include <iostream>

const glm::vec3 Camera::WORLD_UP{ 0.0f, 1.0f, 0.0f };

void Camera::Update(float _deltaTime, sf::Vector2i moveDirection, sf::Vector2i mousePosition) {
	deltaTime = _deltaTime;
	UpdateDirectionVectors();
	if (moveDirection != sf::Vector2i{ 0, 0 }) { UpdatePosition(moveDirection); }
	if (mousePosition != sf::Vector2i{ 0, 0 }) { 
		UpdateRotation(mousePosition); 
	}
	else {
		isRotating = false;
	}
}

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

void Camera::UpdatePosition(sf::Vector2i moveDirection) {
	switch (moveDirection.x) {
	case (1):
		Forward();
		break;
	case (-1):
		Backward();
		break;
	}

	switch (moveDirection.y) {
	case (1):
		Left();
		break;
	case (-1):
		Right();
		break;
	}
}

void Camera::UpdateRotation(sf::Vector2i mousePosition) {
	if (!isRotating) {
		isRotating = true;
		lastMousePos = mousePosition;
	}
	else {
		int xOffset = mousePosition.x - lastMousePos.x;
		int yOffset = lastMousePos.y - mousePosition.y;
		yaw += xOffset * MOUSE_SENSITIVITY * deltaTime;
		pitch += yOffset * MOUSE_SENSITIVITY * deltaTime;
	}
}