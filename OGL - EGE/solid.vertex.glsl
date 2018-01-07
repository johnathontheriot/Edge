#version 330 core

layout(location = 0) in vec3 vertexMSpace;
uniform mat4 viewTransform;
uniform mat4 modelTransform;

void main(){
    gl_Position.xyzw = viewTransform * modelTransform * vec4(vertexMSpace, 1.0);
}
