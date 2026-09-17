#version 330 core

in vec3 o_Normal;
in vec2 o_TexCoord;

uniform sampler2D u_TextureSpecular;

out vec4 FragColor;

void main() {
	FragColor = texture(u_TextureSpecular, o_TexCoord);
}