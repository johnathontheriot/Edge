#version 330 core

layout (location = 4) in vec3 initialVelocity;
layout (location = 5) in float initialTime;

uniform mat4 main_viewTransform;
uniform mat4 modelTransform;
uniform mat4 main_projectionTransform;
uniform float time;
uniform vec3 force;
out float transparency;
void main() {
    vec3 position = (mod(initialTime + time, 10.0) * initialVelocity) + (mod(initialTime + time, 10.0) * force) + (mod(initialTime + time, 10.0) * mod(initialTime + time, 10.0) * vec3(0, -0.08, 0));
    transparency = 1.0 - (mod(initialTime + time, 10.0) * .1);
    gl_Position.xyzw = main_projectionTransform * main_viewTransform * modelTransform * vec4(position, 1.0);
    
}
