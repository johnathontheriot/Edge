#version 400 core

uniform sampler2D tex;

layout (location = 0) out vec4 color;

subroutine vec4 routinePass();
subroutine uniform routinePass routineType;

uniform float weights[8];

subroutine(routinePass)
vec4 blurPass1() {
    ivec2 pixel = ivec2(gl_FragCoord.xy);
    vec4 sum = texelFetch(tex, pixel, 0) * .08966311333;
    float blurFactor = 4.0;

    sum += texelFetchOffset(tex, pixel, 0, ivec2(0, 1)) * .08744932;
    sum += texelFetchOffset(tex, pixel, 0, ivec2(0,-1)) * .08744932;
    
    sum += texelFetchOffset(tex, pixel, 0, ivec2(0,2)) * .08113053;
    sum += texelFetchOffset(tex, pixel, 0, ivec2(0,-2)) * .08113053;
    
    sum += texelFetchOffset(tex, pixel, 0, ivec2(0,3)) * .0715974;
    sum += texelFetchOffset(tex, pixel, 0, ivec2(0,-3)) * .0715974;
    
    sum += texelFetchOffset(tex, pixel, 0, ivec2(0, 4)) * .06010298;
    sum += texelFetchOffset(tex, pixel, 0, ivec2(0,-4)) * .06010298;
    
    sum += texelFetchOffset(tex, pixel, 0, ivec2(0,5)) * .0479932;
    sum += texelFetchOffset(tex, pixel, 0, ivec2(0,-5)) * .0479932;
    
    sum += texelFetchOffset(tex, pixel, 0, ivec2(0,6)) * .0364543;
    sum += texelFetchOffset(tex, pixel, 0, ivec2(0,-6)) * .0364543;
    
    sum += texelFetchOffset(tex, pixel, 0, ivec2(0,7)) * .026339722;
    sum += texelFetchOffset(tex, pixel, 0, ivec2(0,-7)) * .026339722;
    
    sum += texelFetchOffset(tex, pixel, 0, ivec2(0,8)) * .01810266997;
    sum += texelFetchOffset(tex, pixel, 0, ivec2(0,-8)) * .01810266997;
    
    sum += texelFetchOffset(tex, pixel, 0, ivec2(0,9)) * .0118349;
    sum += texelFetchOffset(tex, pixel, 0, ivec2(0,-9)) * .0118349;
    
    sum += texelFetchOffset(tex, pixel, 0, ivec2(0,10)) * .00735999;
    sum += texelFetchOffset(tex, pixel, 0, ivec2(0,-10)) * .00735999;
    
    sum += texelFetchOffset(tex, pixel, 0, ivec2(0,11)) * .00438354;
    sum += texelFetchOffset(tex, pixel, 0, ivec2(0,-11)) * .00438354;
    
    sum += texelFetchOffset(tex, pixel, 0, ivec2(0,12)) * .00244992;
    sum += texelFetchOffset(tex, pixel, 0, ivec2(0,-12)) * .00244992;
    
    return vec4(sum.rgb, 1.0);
}

subroutine(routinePass)
vec4 blurPass2() {
    ivec2 pixel = ivec2(gl_FragCoord.xy);
    vec4 sum = texelFetch(tex, pixel, 0) * .08966311333;
    float blurFactor = 4.0;

    sum += texelFetchOffset(tex, pixel, 0, ivec2(1, 0)) * .08744932;
    sum += texelFetchOffset(tex, pixel, 0, ivec2(-1, 0)) * .08744932;
    
    sum += texelFetchOffset(tex, pixel, 0, ivec2(2, 0)) * .08113053;
    sum += texelFetchOffset(tex, pixel, 0, ivec2(-2, 0)) * .08113053;
    
    sum += texelFetchOffset(tex, pixel, 0, ivec2(3, 0)) * .0715974;
    sum += texelFetchOffset(tex, pixel, 0, ivec2(-3, 0)) * .0715974;
    
    sum += texelFetchOffset(tex, pixel, 0, ivec2(4,0)) * .06010298;
    sum += texelFetchOffset(tex, pixel, 0, ivec2(-4,0)) * .06010298;
    
    sum += texelFetchOffset(tex, pixel, 0, ivec2(5,0)) * .0479932;
    sum += texelFetchOffset(tex, pixel, 0, ivec2(-5,0)) * .0479932;
    
    sum += texelFetchOffset(tex, pixel, 0, ivec2(6,0)) * .0364543;
    sum += texelFetchOffset(tex, pixel, 0, ivec2(-6,0)) * .0364543;
    
    sum += texelFetchOffset(tex, pixel, 0, ivec2(7,0)) * .026339722;
    sum += texelFetchOffset(tex, pixel, 0, ivec2(-7,0)) * .026339722;
    
    sum += texelFetchOffset(tex, pixel, 0, ivec2(8,0)) * .01810266997;
    sum += texelFetchOffset(tex, pixel, 0, ivec2(-8,0)) * .01810266997;
    
    sum += texelFetchOffset(tex, pixel, 0, ivec2(9,0)) * .0118349;
    sum += texelFetchOffset(tex, pixel, 0, ivec2(-9,0)) * .0118349;
    
    sum += texelFetchOffset(tex, pixel, 0, ivec2(10,0)) * .00735999;
    sum += texelFetchOffset(tex, pixel, 0, ivec2(-10,0)) * .00735999;
    
    sum += texelFetchOffset(tex, pixel, 0, ivec2(11,0)) * .00438354;
    sum += texelFetchOffset(tex, pixel, 0, ivec2(-11,0)) * .00438354;

    return vec4(sum.rgb, 1.0);
}


void main(){
    color = routineType();
}
