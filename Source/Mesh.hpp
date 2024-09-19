#pragma once
#include <glm/glm.hpp>
#include <vector>

class Mesh {
public:
	Mesh(std::vector<glm::vec3> vertices, std::vector<uint32_t> indices);
	void Draw() const;

	glm::mat4 transformation;
private:
	const int POINT_SIZE = 3;
	const size_t SIZEOF_POINT = POINT_SIZE * sizeof(float);
	const size_t SIZEOF_VERTICESLIST = sizeof(vertices) / 3;

	std::vector<glm::vec3> vertices{};
	std::vector<uint32_t> indices{};

	uint32_t vertexArray{};
	uint32_t vertexBuffer{};
	uint32_t elementBuffer{};
};

