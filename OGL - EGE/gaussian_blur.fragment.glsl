#version 400 core

uniform sampler2D tex;

layout (location = 0) out vec4 color;

subroutine vec4 routinePass();
subroutine uniform routinePass routineType;

uniform float weights[8];

subroutine(routinePass)
vec4 blurPass1() {
    ivec2 pixel = ivec2(gl_FragCoord.xy);
    vec4 sum = texelFetch(tex, pixel, 0) * 20.0;
    float blurFactor = 4.0;

    sum += texelFetchOffset(tex, pixel, 0, ivec2(0, 1 * 1000)) * 15.0;
    sum += texelFetchOffset(tex, pixel, 0, ivec2(0,-1 * 1000)) * 15.0;
    
    sum += texelFetchOffset(tex, pixel, 0, ivec2(0,2 * 1000)) * 6.0;
    sum += texelFetchOffset(tex, pixel, 0, ivec2(0,-2 * 1000)) * 6.0;
    
    sum += texelFetchOffset(tex, pixel, 0, ivec2(0,3 * 1000));
    sum += texelFetchOffset(tex, pixel, 0, ivec2(0,-3 * 1000));
    
    
    return vec4(sum.r / 64.0, sum.g / 64.0, sum.b / 64.0, 1.0);
}

subroutine(routinePass)
vec4 blurPass2() {
    ivec2 pixel = ivec2(gl_FragCoord.xy);
    vec4 sum = texelFetch(tex, pixel, 0) * 20.0;
    float blurFactor = 4.0;

    sum += texelFetchOffset(tex, pixel, 0, ivec2(1 * 1000, 0)) * 15.0;
    sum += texelFetchOffset(tex, pixel, 0, ivec2(-1 * 1000, 0)) * 15.0;
    
    sum += texelFetchOffset(tex, pixel, 0, ivec2(2 * 1000, 0)) * 6.0;
    sum += texelFetchOffset(tex, pixel, 0, ivec2(-2 * 1000, 0)) * 6.0;
    
    sum += texelFetchOffset(tex, pixel, 0, ivec2(3 * 1000, 0)) ;
    sum += texelFetchOffset(tex, pixel, 0, ivec2(-3 * 1000, 0));

    return vec4(sum.r / 64.0, sum.g / 64.0, sum.b / 64.0, 1.0);
}


void main(){


    
    color = routineType();
}
