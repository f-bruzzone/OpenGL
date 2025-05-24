#shader vertex
#version 330 core

layout(location = 0) in vec3 vp;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

out vec2 v_TexCoord;
uniform mat4 u_MVP;

void main(){
    gl_Position = u_MVP * vec4(vp, 1.0);

    v_TexCoord = texCoord;
};



#shader fragment
#version 330 core


in vec2 v_TexCoord;
uniform sampler2D u_Texture;

out vec3 o_Color;

void main(){
    o_Color = texture(u_Texture, v_TexCoord).rgb;
    //o_Color = vec3(v_TexCoord, 0);
};
