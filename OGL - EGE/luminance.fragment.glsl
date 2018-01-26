#version 330 core

layout (location = 0) out vec4 color;
in vec2 vUV;
uniform sampler2D tex;

float luminance(vec3 rgb) {
    return dot(rgb, vec3(0.2126, 0.7152, 0.0722));
}

void main(){
    float threshold = 0.6;
    color = texture(tex, vec2(vUV.r, vUV.g));
    if(luminance(color.rgb) <= threshold) {
        color = vec4(0, 0, 0, 0);
    }
}
