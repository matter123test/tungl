#version 330 core

in vec3 o_Normal;
in vec2 o_TexCoords;

out vec4 FragColor;

void main() {
	FragColor = vec4(o_Normal, 1.0);
}