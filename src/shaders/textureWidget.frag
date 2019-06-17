#version 450 core

in vec2 out_texcoord;

out vec4 out_color;
uniform sampler2D color_map;


void main()
{
     out_color = vec4(texture(color_map, out_texcoord).xyz, 1.);
}
