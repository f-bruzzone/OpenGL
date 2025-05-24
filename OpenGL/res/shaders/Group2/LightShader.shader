#shader vertex
#version 330 core

layout(location = 0) in vec3 vp;

uniform mat4 u_MVP;

void main(){
    gl_Position = u_MVP * vec4(vp, 1.0);
};



#shader fragment
#version 330 core


out vec4 o_Color;

void main(){
    o_Color = vec4(1);
};
