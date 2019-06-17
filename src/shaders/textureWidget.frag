#version 450 core

layout(location = 0) in vec2 frag_texcoord;

out vec4 out_color;
uniform sampler2D color_map;


void main()
{

     out_color = vec4(texture(color_map, frag_texcoord).xyz, 1.);

}
