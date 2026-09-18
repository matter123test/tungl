#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec3 o_Normal;
out vec2 o_TexCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() {
	o_Normal = aNormal;
	o_TexCoord = aTexCoords;

	gl_Position = projection * view * model * vec4(aPosition, 1.0);
}