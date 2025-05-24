#shader vertex
#version 330 core

layout(location = 0) in vec3 vp;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

out vec2 v_TexCoord;
uniform mat4 u_MVP;

void main(){
    gl_Position = u_MVP * vec4(vp, 1.0);

    v_TexCoord = vec2(texCoord.x, texCoord.y);
};



#shader fragment
#version 330 core


in vec2 v_TexCoord;
uniform sampler2D u_Texture;

out vec4 o_Color;

void main(){
    o_Color = texture(u_Texture, v_TexCoord);
};
