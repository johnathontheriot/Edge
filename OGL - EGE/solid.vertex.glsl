#version 330 core

layout(location = 0) in vec3 vertexMSpace;
layout(location = 1) in vec2 vertexUV;
uniform mat4 viewTransform;
uniform mat4 modelTransform;
out vec2 UV;

void main(){
    gl_Position.xyzw = viewTransform * modelTransform * vec4(vertexMSpace, 1.0);
    UV = vertexUV;
}
