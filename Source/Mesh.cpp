#include "Mesh.hpp"
#include <GL/glew.h>	// modern OpenGL aren't present by default
#include <glm/glm.hpp>

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices, size_t materialIndex) 
	: vertices(vertices), indices(indices), materialIndex(materialIndex)
{
	// Generate Buffers
	glGenBuffers(1, &vertexBuffer);
	glGenBuffers(1, &elementBuffer);
	glGenVertexArrays(1, &vertexArray);

	// Bind
	glBindVertexArray(vertexArray);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	size_t sizeOfVertices = vertices.size() * sizeof(Vertex);
	glBufferData(GL_ARRAY_BUFFER, sizeOfVertices, vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
	size_t sizeOfIndicess = indices.size() * sizeof(glm::uint32_t);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeOfIndicess, indices.data(), GL_STATIC_DRAW);

	// Initialize
	glVertexAttribPointer(0, POINT_SIZE, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, POINT_SIZE, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(1);

	// Un-bind, good practice
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::Draw() const {
	glBindVertexArray(vertexArray);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
}