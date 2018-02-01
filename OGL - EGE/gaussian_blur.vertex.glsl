#version 400 core

layout(location = 0) in vec3 vertexMSpace;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 faceNormals;
layout(location = 3) in vec3 vertexNormals;

void main(){
    gl_Position.xyzw = vec4(vertexMSpace, 1.0);
}
