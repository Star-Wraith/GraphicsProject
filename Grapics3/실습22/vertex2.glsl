#version 330 core

layout (location = 5) in vec3 aPos;   // 위치 변수는 attribute position 0을 가집니다.
layout (location = 6) in vec3 in_Color;
layout (location = 7) in vec3 aNormal;


uniform mat4 modelTransform2;

uniform mat4 viewTransform2;

uniform mat4 projectionTransform2;

out vec3 FragPos; //--- 객체의 위치값을 프래그먼트 세이더로 보낸다.
out vec3 Normal;


void main()
{
	gl_Position = projectionTransform2 * viewTransform2 * modelTransform2 * vec4 (aPos, 1.0); 

	FragPos = vec3(modelTransform2 * vec4(aPos, 1.0)); //--- 객체에 대한 조명 계산을 프래그먼트 셰이더에서 한다. 
	
	Normal = aNormal;
}  
