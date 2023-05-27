#version 330 core

layout (location = 5) in vec3 aPos;   // ��ġ ������ attribute position 0�� �����ϴ�.
layout (location = 6) in vec3 in_Color;
layout (location = 7) in vec3 aNormal;


uniform mat4 modelTransform2;

out vec3 out_Color;



void main()
{
	gl_Position =  modelTransform2 * vec4 (aPos, 1.0); 
   out_Color = in_Color;

}  
