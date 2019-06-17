#version 450 core



vec2 vertices[4] = { vec2(-1.0f, 1.0f), vec2(-1.0f, -1.0f),vec2(1.0f, 1.0f),vec2(1.0f, -1.0f)};

out vec2 out_texcoord;


void main() {

  out_texcoord = (vertices[gl_VertexID] + 1)/2;
  gl_Position = vec4(vertices[gl_VertexID],0,1);

}
