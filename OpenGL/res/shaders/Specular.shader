#shader vertex
#version 330 core

layout(location = 0) in vec3 vp;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

uniform vec3 u_LightPosition;

uniform mat4 u_MVP;
uniform mat4 u_Model;
uniform mat4 u_View;

out vec2 o_TexCoord;

out vec3 normal_cameraspace;
out vec3 lightDirection_cameraspace;
out vec3 position_worldspace;
out vec3 eyeDirection_cameraspace;

void main(){
    gl_Position = u_MVP * vec4(vp, 1.0);

    position_worldspace = (u_Model * vec4(vp, 1.0)).xyz;

    vec3 position_cameraspace = (u_View * u_Model * vec4(vp, 1.0)).xyz;
    eyeDirection_cameraspace = vec3(0, 0, 0) - position_cameraspace;

    vec3 lightPosition_cameraspace = (u_View * vec4(u_LightPosition, 1.0)).xyz;
    lightDirection_cameraspace = lightPosition_cameraspace + eyeDirection_cameraspace;

    normal_cameraspace = (u_View * u_Model * vec4(normal, 0.0)).xyz;

    o_TexCoord = texCoord;
};



#shader fragment
#version 330 core

in vec2 o_TexCoord;

uniform vec3 u_DiffuseColor;
uniform float u_LightPower;
uniform vec3 u_LightPosition;

in vec3 normal_cameraspace;
in vec3 lightDirection_cameraspace;
in vec3 position_worldspace;
in vec3 eyeDirection_cameraspace;

out vec3 o_Color;

void main(){
    vec3 n = normalize(normal_cameraspace);
    vec3 l = normalize(lightDirection_cameraspace);

    vec3 E = normalize(eyeDirection_cameraspace);
    vec3 R = reflect(-l, n);

    float cosAlpha = clamp(dot(E, R), 0, 1);
    float cosTheta = clamp(dot(n, l), 0, 1);

    vec3 lightColor = vec3(1.0, 1.0, 1.0);
    vec3 materialAmbientColor = 0.15 * u_DiffuseColor;

    float distance = length(position_worldspace - u_LightPosition);

    vec3 materialSpecularColor = lightColor * u_LightPower * pow(cosAlpha, 10) / (distance * distance + 0.01);

   o_Color = materialSpecularColor + materialAmbientColor + u_DiffuseColor * lightColor * u_LightPower * cosTheta / (distance * distance + 0.01);
};