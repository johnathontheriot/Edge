#version 330 core

out vec4 color;
in vec2 vUV;
uniform sampler2D tex;
in vec3 ns;
in vec3 light;
in float lIntensity;
in vec3 lColor;

void main(){
    float diffuseComponent = max( dot(normalize(ns) ,normalize(light) ), 0.0 );
    vec3 diffuse = vec3(1, 1, 1) * diffuseComponent;
    color = vec4((lIntensity / 60.0) * diffuse * texture(tex, vec2(vUV.r, - vUV.g)).rgb * lColor, 1.0);
    //color = normalize(ns);
}
