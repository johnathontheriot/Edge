#version 330 core

out vec4 color;
in vec2 vUV;
uniform sampler2D tex;
in vec3 ns;
in vec3 fns;
in float rIntensity;
in vec3 light;
in float lIntensity;
in vec3 lColor;
in vec3 vEye;
uniform samplerCube envtex;
in vec3 view;

void main(){
    float diffuseComponent = max( dot(normalize(ns) ,normalize(light) ), 0.0 );
    vec3 diffuse = vec3(1, 1, 1) * diffuseComponent;
    vec3 normalizedEye = normalize(vEye);
    vec3 lightReflection = reflect(-normalize(light), normalize(fns));
    vec3 envReflection = reflect(view, normalize(ns));
    float intensity = (rIntensity / 100.0);
    float specular = clamp( dot( normalizedEye, normalize(lightReflection) ), 0 ,1 );
    color = vec4((lIntensity / 60.0) * diffuse *  lColor, 1.0);
    color += vec4(pow(specular, 5) * vec3(0.3,0.3,0.3), 1.0);
    color = color * vec4(texture(tex, vec2(vUV.r, - vUV.g)).rgb, color.w);
}
