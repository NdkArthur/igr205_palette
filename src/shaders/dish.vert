#version 450 core


//Ce shader sert a l'affichage de la dish de la palette

vec2 vertices[4] = { vec2(-1.0f, -1.0f), vec2(-1.0f, 1.0f),vec2(1.0f,-1.0f),vec2(1.0f, 1.0f)};

out vec2 vtx_2D_coord;



void main() {

  vtx_2D_coord = (vertices[gl_VertexID] + 1)/2;
  gl_Position = vec4(vertices[gl_VertexID], 0, 1);



}
