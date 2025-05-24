#shader vertex
#version 330 core

layout(location = 0) in vec3 vp;
layout(location = 1) in vec4 a_Color;

uniform mat4 u_MVP;
out vec4 v_Color;

void main(){
    gl_Position = u_MVP * vec4(vp, 1.0);
    v_Color = a_Color;
};



#shader fragment
#version 330 core

in vec4 v_Color;
out vec4 o_Color;

void main(){
    o_Color = v_Color;
};