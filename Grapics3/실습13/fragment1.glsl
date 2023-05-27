#version 330 core

in vec3 coord_Color;
out vec4 FragColor;  

void main()
{
	FragColor = vec4(coord_Color, 1.0f);
}
