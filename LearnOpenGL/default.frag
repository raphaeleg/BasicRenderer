#version 330 core

uniform sampler2D tex0;
uniform sampler2D tex1;

in vec3 vertCol;
in vec2 texCoord;
out vec4 FragColor;

void main()
{
	FragColor = mix(texture(tex0, texCoord), texture(tex1, texCoord), 0.2);
}