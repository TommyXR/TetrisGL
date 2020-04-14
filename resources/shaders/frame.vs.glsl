#version 400

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 tex_coords;

out vec3 tex;


uniform mat4 view;
uniform mat4 projection;


void main() {
    tex = tex_coords;

    gl_Position = projection * view * vec4(position, 1);
}