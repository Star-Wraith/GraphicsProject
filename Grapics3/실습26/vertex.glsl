#version 330 core

layout (location = 0) in vec3 aPos;   // 위치 변수는 attribute position 0을 가집니다.
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;


uniform mat4 modelTransform;

out vec3 outNormal;
out vec2 TexCoord;


void main()
{
	gl_Position =  modelTransform * vec4 (aPos, 1.0); 
   outNormal = aNormal;
	TexCoord = aTexCoord;

}  
