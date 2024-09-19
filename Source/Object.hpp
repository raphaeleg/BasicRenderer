#pragma once
#include "Model.hpp"
#include "Shader.hpp"

class Object {
public:
	Model* model;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale = glm::vec3(1.0f);

	Object(Model* model, glm::vec3 position = {}, glm::vec3 rotation = {}, glm::vec3 scale = glm::vec3(1.0f)) 
		: model(model), position(position), rotation(rotation), scale(scale) {};
	glm::mat4 GetTransformationMatrix() const;
	void Draw(Shader shader, glm::vec3 color);
};

