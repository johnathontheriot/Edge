#version 330 core

out vec4 color;
in vec2 UV;
in vec3 cubeCoords;
in vec4 col;
uniform samplerCube tex;

void main(){
    color = texture(tex, cubeCoords);
}
