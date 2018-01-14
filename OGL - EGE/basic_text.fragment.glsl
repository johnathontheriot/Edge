#version 330 core

out vec4 color;
in vec2 UV;
in vec4 col;
uniform sampler2D tex;

void main(){
    color = texture(tex, vec2(UV.r, - UV.g)) * col;
}
