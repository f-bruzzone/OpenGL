#shader vertex
#version 330 core

layout(location = 0) in vec3 vp;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

out vec3 v_TexCoord;
uniform mat4 u_MVP;

void main(){
    gl_Position = u_MVP * vec4(vp, 1.0);

    v_TexCoord = vp;
};



#shader fragment
#version 330 core


in vec3 v_TexCoord;
uniform samplerCube u_Texture;

out vec4 o_Color;

void main(){
    o_Color = texture(u_Texture, v_TexCoord);
};
