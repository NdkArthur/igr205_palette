#version 450 core

in vec2 vtx_2D_coord;
out vec4 out_color;

struct Blob {
    vec2 center;
    float radius;
    vec3 color;
};

uniform Blob blobs[20];
uniform int nbOfBlobs;
uniform float treshold;

float metaball(float d2, float b) {
    if (d2<=(b*b)) {
        return (1 - 4*pow(d2,3)/(9*pow(b,6)) + 17*pow(d2,2)/(9*pow(b,4)) - 22*d2/(9*pow(b,2)));
    }
    else {
        return 0;
    }
}


void main() {

    float sum = 0;
    vec3 rgb = vec3(0,0,0);

    for (unsigned int i =0; i <nbOfBlobs; i++) {
        float intensity = metaball(distance(blobs[i].center, vtx_2D_coord),blobs[i].radius);
        sum += intensity;
        rgb += intensity * blobs[i].color;
    }
    if (sum >0.7) {
        out_color = vec4(rgb/sum, 1.);
    }
    else {
        out_color = vec4(0.85, 0.83, 0.8, 1.);
    }
}
