#version 330 core

layout (location = 0) in vec3 aPos;   // 위치 변수는 attribute position 0을 가집니다.
layout (location = 1) in vec3 in_Color;
layout (location = 2) in vec3 aNormal;



uniform mat4 modelTransform;

uniform mat4 viewTransform;

uniform mat4 projectionTransform;

out vec3 out_Color;




void main()
{
	gl_Position =  projectionTransform * viewTransform * modelTransform * vec4 (aPos, 1.0); 
   out_Color = in_Color;

}  