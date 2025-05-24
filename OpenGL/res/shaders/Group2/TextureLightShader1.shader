#shader vertex
#version 330 core

layout(location = 0) in vec3 vp;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

layout(location = 3) in vec3 tangent;
layout(location = 4) in vec3 bitangent;

uniform vec3 u_LightPosition;

uniform mat4 u_MVP;
uniform mat4 u_Model;
uniform mat4 u_View;

out vec2 o_NewTexCoord;

out vec3 lightDirection_tangentspace;
out vec3 position_worldspace;
out vec3 eyeDirection_tangentspace;

void main(){
    gl_Position = u_MVP * vec4(vp, 1.0);

    position_worldspace = (u_Model * vec4(vp, 1.0)).xyz;

    vec3 position_cameraspace = (u_View * u_Model * vec4(vp, 1.0)).xyz;
    vec3 eyeDirection_cameraspace = vec3(0, 0, 0) - position_cameraspace;

    vec3 lightPosition_cameraspace = (u_View * vec4(u_LightPosition, 1.0)).xyz;
    vec3 lightDirection_cameraspace = lightPosition_cameraspace + eyeDirection_cameraspace;

    vec3 normal_cameraspace = (u_View * u_Model * vec4(normal, 0.0)).xyz;

    o_NewTexCoord = vec2(texCoord.x * 5, 1 - texCoord.y * 5);
    vec3 tangent_cameraspace = (u_View * u_Model * normalize(vec4(tangent, 0))).xyz;
    vec3 bitangent_cameraspace = (u_View * u_Model * normalize(vec4(bitangent, 0))).xyz;

    mat3 TBN_mat = transpose(mat3(
        tangent_cameraspace,
        bitangent_cameraspace,
        normal_cameraspace
    ));

    lightDirection_tangentspace = TBN_mat * lightDirection_cameraspace;
    eyeDirection_tangentspace = TBN_mat * eyeDirection_cameraspace;
};



#shader fragment
#version 330 core

in vec2 o_NewTexCoord;

uniform float u_LightPower;
uniform vec3 u_LightPosition;
uniform sampler2D u_Texture;
uniform sampler2D u_NormalMap;

in vec3 lightDirection_tangentspace;
in vec3 position_worldspace;
in vec3 eyeDirection_tangentspace;

out vec3 o_Color;

void main(){
    vec3 normal_tangentspace = texture(u_NormalMap, o_NewTexCoord).rgb * 2.0 - 1.0;

    vec3 n = normalize(normal_tangentspace);
    vec3 l = normalize(lightDirection_tangentspace);

    vec3 E = normalize(eyeDirection_tangentspace);
    vec3 R = reflect(-l, n);

    float cosAlpha = clamp(dot(E, R), 0, 1);
    float cosTheta = clamp(dot(n, l), 0, 1);

    vec3 lightColor = vec3(1.0, 1.0, 1.0);

    vec3 materialAmbientColor = 0.15 * texture(u_Texture, o_NewTexCoord).rgb;

    float distance = length(position_worldspace - u_LightPosition);

    vec3 materialSpecularColor = lightColor * u_LightPower * pow(cosAlpha, 10) / (distance * distance + 0.01);

   o_Color = materialSpecularColor + materialAmbientColor + texture(u_Texture, o_NewTexCoord).rgb * lightColor * u_LightPower * cosTheta / (distance * distance + 0.01);
   //o_Color = texture(u_Texture, o_NewTexCoord).rgb;
};