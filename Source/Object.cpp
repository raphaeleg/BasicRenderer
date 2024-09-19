#include "Object.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

void Object::Draw(Shader shader, const Material mat) { 
	shader.Use();
	shader.SetValue("material.diffuse", mat.diffuse);
	shader.SetValue("material.specular", mat.specular);
	shader.SetValue("material.shininess", mat.shininess);
	model->Draw(shader, GetTransformationMatrix()); 
};

glm::mat4 Object::GetTransformationMatrix() const {
	glm::mat4 t = glm::mat4(1.0f);
	
	t = glm::translate(t, position);
	t = t * glm::mat4_cast(glm::quat(glm::radians(rotation)));
	t = glm::scale(t, scale);

	return t;
}