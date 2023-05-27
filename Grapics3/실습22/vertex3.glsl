#version 330 core

layout (location = 0) in vec3 aPos;   // ��ġ ������ attribute position 0�� �����ϴ�.
layout (location = 1) in vec3 in_Color;
layout (location = 2) in vec3 aNormal;



uniform mat4 modelTransform3;

uniform mat4 viewTransform3;

uniform mat4 projectionTransform3;

out vec3 FragPos; //--- ��ü�� ��ġ���� �����׸�Ʈ ���̴��� ������.
out vec3 Normal;


void main()
{
	gl_Position =  projectionTransform3 * viewTransform3 * modelTransform3 * vec4 (aPos, 1.0); 
   	FragPos = vec3(modelTransform3 * vec4(aPos, 1.0)); //--- ��ü�� ���� ���� ����� �����׸�Ʈ ���̴����� �Ѵ�. 
	
	Normal = aNormal;

}  
