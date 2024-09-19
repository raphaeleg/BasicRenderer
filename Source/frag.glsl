#version 330 core

in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

uniform float ambientStrength;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

uniform vec3 baseColor;

void main() { 
	vec3 Ia = lightColor * ambientStrength;	// ambient

	// diffuse
	vec3 N = normalize(Normal);
	vec3 Lm = normalize(lightPos - FragPos);
	vec3 Id = lightColor * max(dot(N,Lm), 0.0);

	// specular
	vec3 V = normalize(viewPos - FragPos);
	vec3 Rm = reflect(-Lm, N);
	vec3 Is = lightColor * pow(max(dot(Rm, V), 0.0), 256) * 0.5;

	vec3 color = (Ia + Id + Is) * baseColor;
	FragColor = vec4(color,1.0); 
}