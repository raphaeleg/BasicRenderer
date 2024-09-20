#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

static std::string ReadTextFile(const std::string fileName) {
	std::ifstream file(fileName);
	if (!file.is_open()) {
		std::cerr << "ERROR: Failed to open " + fileName + "\n";
		return "";
	}
	std::stringstream ss{};
	ss << file.rdbuf();
	file.close();
	return ss.str();
}

static void OutputShaderError(size_t shader) {
	const auto infoBufferSize = 1024;
	char infoLog[infoBufferSize];

	glGetShaderInfoLog(shader, infoBufferSize, nullptr, infoLog);
	perror("Failed to compiler shader!\nInfoLog:");
	perror(infoLog);
}

static void OutputFileError(std::string fileName) {
	std::string message = "ERROR: Failed to load: " + fileName;
	perror(message.c_str());
}