#shader vertex
#version 330 core

layout(location = 0) in vec2 vp;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;

void main(){
    gl_Position = vec4(vp.x, vp.y, 0.0, 1.0);

    v_TexCoord = texCoord;
};



#shader fragment
#version 330 core

in vec2 v_TexCoord;

uniform sampler2D u_Texture;

out vec4 o_Color;

void main(){
    //o_Color = texture(u_Texture, v_TexCoord);

    // inverse color
    o_Color = vec4(1.0 - texture(u_Texture, v_TexCoord).rgb, 1.0);
};
