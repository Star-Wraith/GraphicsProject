#version 330 core

in vec3 out_Color1;
out vec4 FragColor1;

void main()
{
	FragColor1 = vec4(out_Color1, 1.0f);
}
