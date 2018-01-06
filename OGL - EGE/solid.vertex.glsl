#version 330 core

layout(location = 0) in vec3 vertexMSpace;

void main(){
    gl_Position.xyzw = vec4(vertexMSpace, 1.0);
}
