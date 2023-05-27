#version 330 core

in vec3 outNormal;
in vec2 TexCoord;
in vec3 ourColor;

out vec4 FragColor;

uniform sampler2D outTexture; 

void main()
{	FragColor = vec4(ourColor,1.0f);
	FragColor = texture(outTexture, TexCoord) * FragColor;

}
