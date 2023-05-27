#version 330 core

layout (location = 5) in vec3 aPos;   // ��ġ ������ attribute position 0�� �����ϴ�.
layout (location = 6) in vec3 in_Color;
layout (location = 7) in vec3 aNormal;


uniform mat4 modelTransform2;

uniform mat4 viewTransform2;

uniform mat4 projectionTransform2;

out vec3 FragPos; //--- ��ü�� ��ġ���� �����׸�Ʈ ���̴��� ������.
out vec3 Normal;


void main()
{
	gl_Position = projectionTransform2 * viewTransform2 * modelTransform2 * vec4 (aPos, 1.0); 

	FragPos = vec3(modelTransform2 * vec4(aPos, 1.0)); //--- ��ü�� ���� ���� ����� �����׸�Ʈ ���̴����� �Ѵ�. 
	
	Normal = aNormal;
}  
