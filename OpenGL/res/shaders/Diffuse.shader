#shader vertex
#version 330 core

layout(location = 0) in vec3 vp; // vector position un transformed
layout(location = 1) in vec2 texCoord;// not actually used for anything
layout(location = 2) in vec3 normal;

uniform vec3 u_LightPosition;

uniform mat4 u_MVP;
uniform mat4 u_Model;
uniform mat4 u_View;

out vec2 o_TexCoord;

out vec3 normal_cameraspace;
out vec3 lightDirection_cameraspace;
out vec3 position_worldspace;

void main(){
    gl_Position = u_MVP * vec4(vp, 1.0);

    position_worldspace = (u_Model * vec4(vp, 1.0)).xyz;

    vec3 position_cameraspace = (u_View * u_Model * vec4(vp, 1.0)).xyz;
    //vec3 eyeDirection_cameraspace = vec3(0, 0, 0) - position_cameraspace;

    vec3 lightPosition_cameraspace = (u_View * vec4(u_LightPosition, 1.0)).xyz;
    //lightDirection_cameraspace = lightPosition_cameraspace + eyeDirection_cameraspace;
    lightDirection_cameraspace = lightPosition_cameraspace - position_cameraspace;

    normal_cameraspace = (u_View * u_Model * vec4(normal, 0.0)).xyz;

    o_TexCoord = texCoord;
};



#shader fragment
#version 330 core

in vec2 o_TexCoord;

uniform vec3 u_DiffuseColor;
uniform float u_LightPower;
uniform vec3 u_LightPosition;

in vec3 normal_cameraspace;
in vec3 lightDirection_cameraspace;
in vec3 position_worldspace;

out vec3 o_Color;

void main(){
    vec3 n = normalize(normal_cameraspace);
    vec3 l = normalize(lightDirection_cameraspace);

    float cosTheta = clamp(dot(n, l), 0, 1);

    vec3 lightColor = vec3(1.0, 1.0, 1.0);
    vec3 materialAmbientColor = 0.15 * u_DiffuseColor;

    float distance = length(position_worldspace - u_LightPosition);

   o_Color = materialAmbientColor + u_DiffuseColor * lightColor * u_LightPower * cosTheta / (distance * distance + 0.01);
   //o_Color = u_DiffuseColor * lightColor * u_LightPower * cosTheta / (distance * distance + 0.01);
};

/*
    The light calculations revolve around finding the dot product between the vertex normal and the direction the light
    is hitting the surface(vertex position in world space). However, we need to convert both the vertex normal and light direction into camera space (after
    the view transformation) to accurately determine this value. Why? Because between the camera space and world space, the world space technically has 
    the most accurate representation of our simulation if we could somehow look into the computer and actually look at it. However we need a camera, and
    so if we were to do these calculations in world space, we would have all of our positions defined with the world space origin (surface/vector position,
    light position, and camera position). In camera space, these positions are not the same as world space and are actually less accurate, but the directions
    DO remain accurate. In camera space all we have to worry about are the positions of the surface and the light because the camera is already accounted for
    because it is always at the origin. That work is done in the vertex shader and relevant values are passed to the fragment shader. REMEMBER:
    the vertex shader runs PER VERTEX, the fragment shader runs PER PIXEL. Most likely you want to handle as much work as you can outide of the fragment
    shader (ideally on the CPU like we do with the MVP matrix for example if possible). 

    NOTE: When calculating distance, this DOES require world space because the distance between two points must be accurate in order to get an accurate value,
    only direction maintains accuracy in camera space.
*/