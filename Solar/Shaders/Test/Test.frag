#version 460 core

in vec3 position;
in vec2 texcoord;
in vec3 normal;
in vec4 vcolor;
out vec4 color;


void main() {
    color = vcolor;
}