#version 450 core

layout(location = 0) in vec3 frag_position;
layout(location = 1) in vec2 frag_texcoord;
layout(location = 2) in vec3 frag_normal;




out vec4 out_color;


void main()
{

    out_color = vec4(frag_texcoord,1., 1.);
    return;


}
