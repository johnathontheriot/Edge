#version 330 core

layout(location = 0) in vec3 vertexMSpace;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 faceNormals;
layout(location = 3) in vec3 vertexNormals;
layout(location = 4) in vec3 tangent;
layout(location = 5) in vec3 bitangent;

uniform mat4 main_viewTransform;
uniform mat4 modelTransform;
uniform mat4 main_projectionTransform;
uniform mat4 invTransMV;
uniform mat4 cmapTransform;
uniform mat4 shadowBias;
uniform mat4 depth_projectionTransform;
uniform mat4 depth_viewTransform;
uniform vec3 light_position;
uniform float light_intensity;
uniform float reflection;
uniform vec3 light_color;
out vec2 vUV;
out vec3 ns;
out vec3 fns;
out vec3 light;
out vec4 shadowPosition;
out float lIntensity;
out vec3 lColor;
out vec3 view;
out vec3 vEye;
out float rIntensity;
out vec4 t;
void main(){
    gl_Position.xyzw = main_projectionTransform * main_viewTransform * modelTransform * vec4(vertexMSpace, 1.0);
    view = (cmapTransform * main_viewTransform * modelTransform * vec4(vertexMSpace, 1.0)).xyz;
    vec3 vertexVSpace = (main_viewTransform * modelTransform * vec4(vertexMSpace, 1.0)).xyz;
    vec3 eyeVSpace = vec3(0.0, 0.0, 0.0) - vertexVSpace;
    vEye = eyeVSpace;
    vUV = vertexUV;
    rIntensity = reflection;
    light = (main_viewTransform  * vec4(light_position, 1.0)).xyz;
    light = light + eyeVSpace;
    ns = normalize((invTransMV * vec4(vertexNormals, 0.0)).xyz);
    fns = normalize((invTransMV * vec4(faceNormals, 0.0)).xyz);
    vec3 tangentEye = normalize(mat3(invTransMV) * tangent.xyz);
    vec3 bitangentEye = normalize(mat3(invTransMV) * bitangent.xyz);
    lIntensity = light_intensity;
    lColor = light_color;
    mat3 tangentSpace = mat3(tangentEye.x, bitangentEye.x, ns.x,
                             tangentEye.y, bitangentEye.y, ns.y,
                             tangentEye.z, bitangentEye.z, ns.z);
    light = tangentSpace * light;
    vEye = tangentSpace * vEye;
    t = vec4(tangent, 1);
    shadowPosition = shadowBias * depth_projectionTransform * depth_viewTransform * modelTransform * vec4(vertexMSpace, 1.0);
    
}
