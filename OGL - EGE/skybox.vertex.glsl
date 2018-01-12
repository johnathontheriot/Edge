#version 330 core

layout(location = 0) in vec3 vertexMSpace;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 colors;
uniform mat4 viewTransform;
uniform mat4 modelTransform;
uniform mat4 projectionTransform;
out vec2 UV;
out vec3 col;

void main(){
    gl_Position.xyzw = projectionTransform * viewTransform * modelTransform * vec4(vertexMSpace, 1.0);
    UV = vertexUV;
    col = colors;
}
