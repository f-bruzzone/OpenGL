#shader vertex
#version 330 core

layout(location = 0) in vec2 vp;

void main(){
    gl_Position = vec4(vp, 0.0, 1.0);
};



#shader fragment
#version 330 core

out vec4 o_Color;

void main(){
    o_Color = vec4(1.0, 0.5, 0.5, 1.0);
};
