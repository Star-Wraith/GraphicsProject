#version 330 core

layout (location = 0) in vec3 aPos;   // 위치 변수는 attribute position 0을 가집니다.
layout (location = 1) in vec3 in_Color;
layout (location = 2) in vec3 aNormal;



uniform mat4 modelTransform;

uniform mat4 viewTransform;

uniform mat4 projectionTransform;

out vec3 FragPos; //--- 객체의 위치값을 프래그먼트 세이더로 보낸다.
out vec3 Normal;


void main()
{
	gl_Position =  projectionTransform * viewTransform * modelTransform * vec4 (aPos, 1.0); 
   	FragPos = vec3(modelTransform * vec4(aPos, 1.0)); //--- 객체에 대한 조명 계산을 프래그먼트 셰이더에서 한다. 
	
	Normal = aNormal;

}  
