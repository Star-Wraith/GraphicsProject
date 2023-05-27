#version 330 core

layout (location = 7) in vec3 aPos1;   // 위치 변수는 attribute position 0을 가집니다.
layout (location = 8) in vec3 in_Color1;
layout (location = 9) in vec3 aNormal1;


uniform mat4 modelTransformC1;
uniform mat4 viewTransform3;

uniform mat4 projectionTransform3;

out vec3 out_Color1;



void main()
{
	gl_Position =  projectionTransform3 * viewTransform3 * modelTransformC1 * vec4 (aPos1, 1.0); 
   out_Color1 = in_Color1;

}  
