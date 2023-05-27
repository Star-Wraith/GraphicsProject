#version 330 core

in vec3 outNormal;
in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D outTexture;

void main()
{
	FragColor = texture(outTexture, TexCoord);
}
