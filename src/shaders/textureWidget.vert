#version 450 core

in vec3 vtx_position;

out vec2 out_texcoord;


void main() {


  out_texcoord = Vec2((vtx_position[0]+1)/2, (vtx_position[1]+1)/2);

}
