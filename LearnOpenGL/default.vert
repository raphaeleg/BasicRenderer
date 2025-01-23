#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;

uniform float scale;

out vec3 vertCol;

void main()
{
	gl_Position = vec4(aPos+aPos*scale, 1.0);
	vertCol = aCol;
}