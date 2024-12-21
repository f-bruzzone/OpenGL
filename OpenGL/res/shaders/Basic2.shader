#shader vertex
#version 330 core

layout(location = 0) in vec2 vp;
layout(location = 1) in vec4 a_Color;

out vec4 v_Color;

void main(){
    gl_Position = vec4(vp, 0.0, 1.0);
    v_Color = a_Color;
};



#shader fragment
#version 330 core

in vec4 v_Color;
out vec4 o_Color;

void main(){
    o_Color = v_Color;
};