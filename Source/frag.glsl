#version 330 core

in vec3 Normal;

out vec4 FragColor;

uniform float ambientStrength;
uniform vec3 lightColor;
uniform vec3 lightPos;

uniform vec3 baseColor;

void main() { 
	vec3 color = vec3(0.0);

	vec3 ambient = lightColor * ambientStrength;
	color += ambient * baseColor;

	FragColor = vec4(color,1.0); 
}