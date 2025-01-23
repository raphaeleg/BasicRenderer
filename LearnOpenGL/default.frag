#version 330 core

uniform float scale;

in vec3 vertCol;
out vec4 FragColor;

void main()
{
	FragColor = vec4(vertCol+scale, 1.0f);
}