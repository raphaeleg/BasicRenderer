#include "Scene.hpp"
#include "Helper.hpp"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

Scene::Scene(const std::string fileName) {
	Assimp::Importer importer;

	importer.ReadFile(fileName, aiProcess_Triangulate);
	const aiScene* scene = importer.GetScene();
	if (!scene || !scene->mRootNode || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) {
		OutputFileError(fileName);
		return;
	}

	processNode(scene->mRootNode, scene, glm::mat4(1.0f));

	for (size_t i = 0; i < scene->mNumMaterials; i++) {
		materials.push_back(processMaterial(scene->mMaterials[i]));
	}
}

void Scene::Draw(Shader shader) {
	for (const Mesh mesh : meshes) {
		const Material mat = materials[mesh.materialIndex];

		shader.Use();
		shader.SetValue("material.diffuse", mat.diffuse);
		shader.SetValue("material.specular", mat.specular);
		shader.SetValue("material.shininess", mat.shininess);

		shader.SetValue("scene", mesh.transformation);
		mesh.Draw();
	}
}

void Scene::processNode(aiNode* node, const aiScene* scene, glm::mat4 parentTransformation) {
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

Mesh Scene::processMesh(aiMesh* mesh) {
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;

	for (size_t i = 0; i < mesh->mNumVertices; i++) {
		aiVector3D pos = mesh->mVertices[i];
		aiVector3D norm = mesh->mNormals[i];
		Vertex vertex{ 
			glm::vec3(pos.x, pos.y, pos.z), 
			glm::vec3(norm.x, norm.y, norm.z)
		};
		vertices.push_back(vertex);
	}

	for (size_t i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for (size_t i = 0; i < face.mNumIndices; i++) {
			indices.push_back(face.mIndices[i]);
		}
	}

	return Mesh(vertices, indices, mesh->mMaterialIndex);
}
 
Material Scene::processMaterial(aiMaterial* mat) {
	aiColor3D diffuse;
	aiColor3D specular;
	float shine;

	mat->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse);
	mat->Get(AI_MATKEY_COLOR_SPECULAR, specular);
	auto shininess = mat->Get(AI_MATKEY_SHININESS, shine);

	return {
		glm::vec3(diffuse.r, diffuse.g, diffuse.b),
		glm::vec3(specular.r, specular.g, specular.b),
		shine
	};
}