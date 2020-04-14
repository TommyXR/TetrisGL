#version 400

out vec4 gl_FragColor;

in vec3 vert_normal;
in vec3 pos;

uniform vec3 color;


const vec3 light_color = vec3(1, 1, 1);
const vec3 light_direction = normalize(vec3(0, 1, 2));


const float kAmbient = 0.7;
const float kDiffuse = 0.7;
const float kSpecular = 0.7;

const float shininess = 15.2;



void main() {

    vec3 ambient = kAmbient * color;

    vec3 diffuse = kDiffuse * color;
    diffuse *= max(dot(normalize(vert_normal), normalize(light_direction)), 0);

    vec3 view_dir = normalize(vec3(0, 0, 0) - pos);
    vec3 reflect_dir = reflect(-light_direction, normalize(vert_normal));


    vec3 specular = kSpecular * light_color;
    specular *= pow(max(dot(view_dir, reflect_dir), 0), shininess);

    gl_FragColor = vec4(ambient + diffuse + specular, 1);
}