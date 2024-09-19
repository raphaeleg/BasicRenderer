#pragma once
#include <string>
#include "Mesh.hpp"
#include "Shader.hpp"
#include <assimp/scene.h>

struct Material {
	glm::vec3 diffuse = glm::vec3(0.0f);
	glm::vec3 specular = glm::vec3(0.0f);
	float shininess = 0.1f;
	Material() {};
	Material(glm::vec3 diffuse, glm::vec3 specular, float shininess)
		: diffuse(diffuse), specular(specular), shininess(shininess) {};
};

class Scene {
public:
	Scene(const std::string fileName);
	void Draw(Shader shader);
private:
	void processNode(aiNode* node, const aiScene* scene, glm::mat4 parentTransformation);
	Material processMaterial(aiMaterial* material);
	Mesh processMesh(aiMesh* mesh);
	std::vector <Mesh> meshes;
	std::vector <Material> materials;
};