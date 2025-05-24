#shader vertex
#version 330 core

layout(location = 0) in vec3 vp;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

out vec2 v_TexCoord;
out vec3 v_Normal;
out vec3 v_VP;

uniform mat4 u_MVP;

void main(){
    gl_Position = u_MVP * vec4(vp, 1.0);

    v_VP = vp;
    v_TexCoord = vec2(texCoord.x, texCoord.y);
    v_Normal = normal;
};



#shader fragment
#version 330 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
};

uniform Material material;

in vec3 v_Normal;
in vec2 v_TexCoord;
in vec3 v_VP;

uniform vec3 u_LightLocation;
uniform vec3 u_CameraPosition;

out vec3 o_Color;

void main(){
    vec3 texColor = texture(material.diffuse, v_TexCoord).rgb;

    vec3 ambient = texColor * 0.2;

    vec3 lightDir = normalize(u_LightLocation - v_VP);
    float cosTheta = max(dot(lightDir, v_Normal), 0);
    vec3 diffuse = texColor * cosTheta;

    vec3 reflected = reflect(-lightDir, v_Normal);
    vec3 eyeDir = normalize(u_CameraPosition - v_VP);
    float specFrac = max(dot(reflected, eyeDir), 0);
    vec3 specular = texColor * pow(specFrac, 32) * texture(material.specular, v_TexCoord).rgb;

    float distance = distance(v_VP, u_LightLocation);
    o_Color = (ambient + diffuse + specular * 2) * 10 / pow(distance, 2);
};
