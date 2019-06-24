#version 450 core

//Sert a afficher la texture en 2D

in vec2 vtx_texcoord;
out vec4 out_color;
uniform sampler2D color_map;

void main() {
    out_color = vec4(texture(color_map, vtx_texcoord).xyz, 1.);
}
