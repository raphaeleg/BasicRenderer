#include "Model.hpp"
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

Model::Model(const std::string fileName) {
	Assimp::Importer importer;
	importer.ReadFile(fileName, aiProcess_Triangulate);

	const aiScene* scene = importer.GetScene();
	if (!scene || !scene->mRootNode || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) {
		std::cerr << "ERROR: Failed to load " << fileName << "\n";
		return;
	}
	processNode(scene->mRootNode, scene, glm::mat4(1.0f));
}

void Model::Draw(Shader shader, glm::mat4 transformation) {
	for (const Mesh mesh : meshes) {
		shader.Use();
		shader.SetValue("model", mesh.transformation * transformation);
		mesh.Draw();
	}
}

void Model::processNode(aiNode* node, const aiScene* scene, glm::mat4 parentTransformation) {
	const auto t = node->mTransformation;
	glm::mat4 transformation = {
		{t.a1, t.b1, t.c1, t.d1},
		{t.a2, t.b2, t.c2, t.d2},
		{t.a3, t.b3, t.c3, t.d3},
		{t.a4, t.b4, t.c4, t.d4}
	};
	transformation = parentTransformation * transformation;

	for (size_t i = 0; i < node->mNumMeshes; i++) {
		Mesh mesh = processMesh(scene->mMeshes[node->mMeshes[i]]);
		mesh.transformation = transformation;
		meshes.push_back(mesh);
	}

	for (size_t i = 0; i < node->mNumChildren; i++) {
		processNode(node->mChildren[i], scene, transformation);
	}
}

Mesh Model::processMesh(aiMesh* mesh) {
	std::vector<glm::vec3> vertices;
	std::vector<uint32_t> indices;

	for (size_t i = 0; i < mesh->mNumVertices; i++) {
		aiVector3D vec = mesh->mVertices[i];
		vertices.push_back(glm::vec3(vec.x, vec.y, vec.z));
	}

	for (size_t i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for (size_t i = 0; i < face.mNumIndices; i++) {
			indices.push_back(face.mIndices[i]);
		}
	}

	return Mesh(vertices, indices);
}