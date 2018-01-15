#version 330 core

layout(location = 0) in vec3 vertexMSpace;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormals;
uniform mat4 viewTransform;
uniform mat4 modelTransform;
uniform mat4 projectionTransform;
uniform mat4 invTransMV;
out vec2 vUV;
out vec3 ns;
out vec3 light;

void main(){
    gl_Position.xyzw = projectionTransform * viewTransform * modelTransform * vec4(vertexMSpace, 1.0);
    vec3 vertexVSpace = (viewTransform * modelTransform * vec4(vertexMSpace, 1.0)).xyz;
    vec3 eyeVSpace = vec3(0.0, 0.0, 0.0) - vertexVSpace;
    vUV = vertexUV;
    light = (viewTransform  * vec4(1.0, 1.0, 1.0, 1.0)).xyz;
    light = light + eyeVSpace;
    ns = (invTransMV * vec4(vertexNormals, 0.0)).xyz;


}
