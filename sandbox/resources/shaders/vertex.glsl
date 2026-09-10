#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec4 aColor;

out vec3 color;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() {
	color = aColor.rgb;
	gl_Position = projection * view * model * vec4(aPosition, 1.0);
}