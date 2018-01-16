#version 330 core

layout(location = 0) in vec3 vertexMSpace;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormals;
uniform mat4 main_viewTransform;
uniform mat4 modelTransform;
uniform mat4 main_projectionTransform;
uniform mat4 invTransMV;
uniform vec3 light_position;
uniform float light_intensity;
uniform vec3 light_color;
out vec2 vUV;
out vec3 ns;
out vec3 light;
out float lIntensity;
out vec3 lColor;


void main(){
    gl_Position.xyzw = main_projectionTransform * main_viewTransform * modelTransform * vec4(vertexMSpace, 1.0);
    vec3 vertexVSpace = (main_viewTransform * modelTransform * vec4(vertexMSpace, 1.0)).xyz;
    vec3 eyeVSpace = vec3(0.0, 0.0, 0.0) - vertexVSpace;
    vUV = vertexUV;
    light = (main_viewTransform  * vec4(light_position, 1.0)).xyz;
    light = light + eyeVSpace;
    ns = (invTransMV * vec4(vertexNormals, 0.0)).xyz;
    lIntensity = light_intensity;
    lColor = light_color;

}
