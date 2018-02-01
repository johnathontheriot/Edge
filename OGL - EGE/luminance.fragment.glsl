#version 330 core

layout (location = 0) out vec4 color;
in vec2 vUV;
uniform sampler2D tex;

in float vlowerThreshold;
in float vupperThreshold;

float luminance(vec3 rgb) {
    return dot(rgb, vec3(0.2126, 0.7152, 0.0722));
}

void main(){
    color = texture(tex, vec2(vUV.r, vUV.g));
    float l = luminance(color.rgb);
    color = color * 4.0 * smoothstep(vlowerThreshold, vupperThreshold, l);
}
