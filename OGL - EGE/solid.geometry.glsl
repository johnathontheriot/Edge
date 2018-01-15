#version 330 core

layout(triangles) in;
layout(triangle_strip, max_vertices=3) out;
out vec2 UV;

in vec2 vUV[3];
void main()
{
    for(int i=0; i<3; i++)
    {
        gl_Position = gl_in[i].gl_Position;
        UV = vUV[i];
        EmitVertex();
    }
    EndPrimitive();
}  
