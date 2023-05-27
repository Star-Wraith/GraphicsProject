#version 330 core

layout (location = 3) in vec3 aPos1;   // 위치 변수는 attribute position 0을 가집니다.
layout (location = 4) in vec3 in_Color1;




out vec3 coord_Color;


void main()
{
   gl_Position =  vec4 (aPos1, 1.0); 
   coord_Color = in_Color1;


}  
