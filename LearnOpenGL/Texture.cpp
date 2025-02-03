#include"Texture.hpp"

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType) : type(texType), slot(slot) {
	int width, height, numColCh = 0;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load(image, &width, &height, &numColCh, 0);

	glGenTextures(1, &ID);	// Generate
	glActiveTexture(slot);	// Assign
	glBindTexture(texType, ID);

	// Sampling options
	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Wrap options
	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

	if (bytes) {
		glTexImage2D(texType, 0, format, width, height, 0, format, pixelType, bytes);
		glGenerateMipmap(texType);
	} else {
		std::cout << "ERROR: Generating texture " << image << std::endl;
	}

	// Deallocate
	stbi_image_free(bytes);
	glBindTexture(texType, 0);
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit) {
	shader.Activate();
	shader.setInt(uniform, unit);
}