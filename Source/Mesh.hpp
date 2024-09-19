#pragma once
#include <glm/glm.hpp>
#include <vector>

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	Vertex(glm::vec3 position, glm::vec3 normal) : position(position), normal(normal) {};
};

class Mesh {
public:
	Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices);
	void Draw() const;

	glm::mat4 transformation;
private:
	const int POINT_SIZE = 3;
	const size_t SIZEOF_VERTICESLIST = sizeof(vertices) / 3;

	std::vector<Vertex> vertices{};
	std::vector<uint32_t> indices{};

	uint32_t vertexArray{};
	uint32_t vertexBuffer{};
	uint32_t elementBuffer{};
};