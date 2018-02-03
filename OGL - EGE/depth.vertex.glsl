#version 330 core

layout(location = 0) in vec3 vertexMSpace;

uniform mat4 main_viewTransform;
uniform mat4 modelTransform;
uniform mat4 main_projectionTransform;

void main(){
    gl_Position.xyzw = main_projectionTransform * main_viewTransform * modelTransform * vec4(vertexMSpace, 1.0);
}
