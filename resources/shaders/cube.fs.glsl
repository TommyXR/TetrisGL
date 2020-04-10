#version 400

out vec4 gl_FragColor;

in vec3 vert_normal;

uniform vec3 color;


void main() {

    gl_FragColor = vec4(color + vert_normal / 4, 1);
}