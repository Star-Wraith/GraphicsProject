#version 330 core

layout (location = 5) in vec3 aPos;   // ��ġ ������ attribute position 0�� �����ϴ�.
layout (location = 6) in vec3 in_Color;


uniform mat4 modelTransform2;

uniform mat4 viewTransform2;

uniform mat4 projectionTransform2;

out vec3 out_Color;



void main()
{
	gl_Position = projectionTransform2 * viewTransform2 * modelTransform2 * vec4 (aPos, 1.0); 
   out_Color = in_Color;

}  
