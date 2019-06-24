#version 450 core

layout(location = 0) in vec3 frag_position;
layout(location = 1) in vec2 frag_texcoord;
layout(location = 2) in vec3 frag_normal;


// ce shader sert a renvoyer les coordonnees de textures par picking sur le modele 3D

out vec4 out_color;


void main()
{

    out_color = vec4(frag_texcoord,1., 1.);
    return;


}
