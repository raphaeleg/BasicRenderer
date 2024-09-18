#pragma once
#include "Mesh.hpp"
#include "Shader.hpp"

class Object {
public:
	const Mesh* mesh;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale = glm::vec3(1.0f);

	Object(const Mesh* mesh, glm::vec3 position = {}, glm::vec3 rotation = {}, glm::vec3 scale = glm::vec3(1.0f)) 
		: mesh(mesh), position(position), rotation(rotation), scale(scale) {};
	glm::mat4 GetTransformationMatrix() const;
	void Draw(Shader shader, glm::vec3 color);
};

