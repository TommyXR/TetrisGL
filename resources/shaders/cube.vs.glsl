#version 400

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

out vec3 vert_normal;
out vec3 pos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main() {
    vert_normal = normal;

    gl_Position = projection * view * model * vec4(position, 1);
}