#version 330 core

out vec4 color;
in vec2 vUV;
uniform sampler2D tex;
in vec3 ns;
in vec3 fns;
in vec3 light;
in float lIntensity;
in vec3 lColor;
uniform samplerCube envtex;
in vec3 view;

void main(){
    float diffuseComponent = max( dot(normalize(ns) ,normalize(light) ), 0.0 );
    vec3 diffuse = vec3(1, 1, 1) * diffuseComponent;
    vec3 envReflection = reflect(view, normalize(fns));
    vec4 reflectionColor = texture(envtex, envReflection);
    vec3 range = vec3(1.0, 1.0, 1.0) - reflectionColor.xyz;
    float intensity = (100 / 100.0);
    vec3 amnt = range * (intensity);
    reflectionColor = vec4(vec3(1.0, 1.0, 1.0) - amnt, reflectionColor.w);
    color = vec4((lIntensity / 60.0) * diffuse * texture(tex, vec2(vUV.r, - vUV.g)).rgb * lColor, 1.0) * reflectionColor;
    //color = normalize(ns);
}
