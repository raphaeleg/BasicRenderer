#pragma once
#include "Model.hpp"
#include "Shader.hpp"

struct Material {
	glm::vec3 diffuse = glm::vec3(0.0f);
	glm::vec3 specular = glm::vec3(0.0f);
	float shininess = 0.1f;
	Material() {};
	Material(glm::vec3 diffuse, glm::vec3 specular, float shininess)
		: diffuse(diffuse), specular(specular), shininess(shininess) {};
};

class Object {
public:
	Model* model;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale = glm::vec3(1.0f);

	Object(Model* model, glm::vec3 position = {}, glm::vec3 rotation = {}, glm::vec3 scale = glm::vec3(1.0f)) 
		: model(model), position(position), rotation(rotation), scale(scale) {};
	glm::mat4 GetTransformationMatrix() const;
	void Draw(Shader shader, const Material mat = {});
};

