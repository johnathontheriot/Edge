#version 330 core

in float transparency;
uniform sampler2D tex;

layout (location = 0) out vec4 color;

void main() {
    color = texture(tex, gl_PointCoord) * vec4(1.0, 1.0, 1.0, transparency);
}
