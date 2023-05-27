#version 330
//--- in_Position: attribute index 0 
//--- in_Color: attribute index 1

layout (location = 0) in vec3 in_Position; //--- 위치 변수: attribute position 0
layout (location = 1) in vec3 in_Color; //--- 컬러 변수: attribute position 1
uniform mat4 modelTransform;
out vec3 out_Color;



void main(void) 
{
  gl_Position = modelTransform * vec4 (in_Position.x, in_Position.y, in_Position.z, 1.0);
  out_Color = in_Color;
}