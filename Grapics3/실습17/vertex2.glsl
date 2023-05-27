#version 330 core

layout (location = 5) in vec3 aPos2;   // 위치 변수는 attribute position 0을 가집니다.
layout (location = 6) in vec3 in_Color2;

uniform mat4 modelTransform2;

uniform mat4 viewTransform2;

uniform mat4 projectionTransform2;

out vec3 out_Color;


void main()
{
   gl_Position =   projectionTransform2 * viewTransform2 *modelTransform2 * vec4 (aPos2, 1.0); 
   out_Color = in_Color2;


}  
