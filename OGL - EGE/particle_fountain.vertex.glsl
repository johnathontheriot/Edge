#version 330 core

layout (location = 0) in vec3 initialVelocity;
layout (location = 1) in float initialTime;

uniform mat4 main_viewTransform;
uniform mat4 modelTransform;
uniform mat4 main_projectionTransform;
uniform float time;
uniform vec3 force;
out float transparency;
void main() {
    vec3 position = (mod(time, 10.0) * initialVelocity) + (mod(time, 10.0) * force);
    transparency = 1.0 - (mod(time, 10.0) * .1);
    gl_Position.xyzw = main_projectionTransform * main_viewTransform * modelTransform * vec4(position, 1.0);
    
}
