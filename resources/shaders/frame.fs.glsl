#version 400

out vec4 gl_FragColor;


in vec3 tex;

uniform vec3 color;

uniform sampler2D frame_texture;



void main() {

    vec4 tex_color = vec4(0, 0.5, 0.8, 1) * texture(frame_texture, tex.xy);

    gl_FragColor = tex_color;
}