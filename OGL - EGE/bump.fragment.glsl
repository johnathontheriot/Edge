#version 330 core

out vec4 color;
in vec2 vUV;
uniform sampler2DShadow shadowMap;
uniform sampler2D tex;
uniform sampler2D bump;
in vec3 ns;
in vec3 fns;
in float rIntensity;
in vec3 light;
in float lIntensity;
in vec3 lColor;
in vec3 vEye;
uniform samplerCube envtex;
in vec3 view;
in vec4 shadowPosition;
in vec4 t;

void main(){
    vec3 normal = 2.0 * texture(bump, vec2(vUV.r, - vUV.g)).rgb - 1.0;
    float diffuseComponent = max( dot(normalize(normal) ,normalize(light) ), 0.0 );
    vec3 diffuse = vec3(1, 1, 1) * diffuseComponent;
    vec3 normalizedEye = normalize(vEye);
    vec3 lightReflection = reflect(-normalize(light), normalize(normal));
    vec3 envReflection = reflect(view, normalize(normal));
    float intensity = (rIntensity / 100.0);
    float specular = clamp( dot( normalizedEye, normalize(lightReflection) ), 0 ,1 );
    color = vec4((lIntensity / 60.0) * diffuse *  lColor, 1.0);
    color += vec4(pow(specular, 30) * vec3(0.3,0.3,0.3), 1.0);
    color = color * vec4(texture(tex, vec2(vUV.r, - vUV.g)).rgb, color.w);
    float visibility = textureProj(shadowMap, shadowPosition);
    
    color = color * visibility;
    //color = t;
    //color = vec4(texture(tex, vec2(vUV.r, - vUV.g)).r, texture(tex, vec2(vUV.r, - vUV.g)).r, texture(tex, vec2(vUV.r, - vUV.g)).r, color.w);
    
}
