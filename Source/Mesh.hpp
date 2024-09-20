#pragma once
#include <glm/glm.hpp>
#include <vector>

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	Vertex(glm::vec3 position, glm::vec3 normal) 
		: position(position), normal(normal) {};
};

class Mesh {
public:
	glm::mat4 transformation{};
	size_t materialIndex = 0;

	Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices, size_t materialIndex = 0);
	void Draw() const;
private:
	static constexpr int POINT_SIZE = 3;
	const size_t SIZEOF_VERTICESLIST = sizeof(vertices) / 3;

	uint32_t vertexArray{};
	uint32_t vertexBuffer{};
	uint32_t elementBuffer{};

	std::vector<Vertex> vertices{};
	std::vector<uint32_t> indices{};
};