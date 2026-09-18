#version 330 core

in vec3 o_Normal;
in vec2 o_TexCoord;

uniform sampler2D u_TextureSpecular1;
uniform sampler2D u_TextureSpecular2;

out vec4 FragColor;

void main() {
	FragColor = mix(
		texture(u_TextureSpecular1, o_TexCoord),
		texture(u_TextureSpecular2, o_TexCoord),
		0.5
	);
}