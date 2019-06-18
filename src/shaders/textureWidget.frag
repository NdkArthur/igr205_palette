#version 450 core

in vec2 vtx_texcoord;


out vec4 out_color;
uniform vec2 click_coord;
uniform vec3 brush_color;
uniform sampler2D color_map;



void main() {
    if(distance(click_coord, vtx_texcoord) > 0.05) {
        out_color = vec4(texture(color_map, vtx_texcoord).xyz, 1.);
       }
    else {
        out_color = vec4(brush_color,1.);
    }
}
