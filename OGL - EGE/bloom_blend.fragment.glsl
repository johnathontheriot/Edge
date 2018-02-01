#version 330 core

layout (location = 0) out vec4 color;
in vec2 vUV;
uniform sampler2D scene;
uniform sampler2D blur;

void main(){
    vec4 sC = texture(scene, vec2(vUV.r, vUV.g)) * 1.0;
    vec4 bC = texture(blur, vec2(vUV.r, vUV.g)) * 1.0;
    color = bC;
    color.rgb = vec3(1.0) - exp(-color.rgb *  0.9);
}
