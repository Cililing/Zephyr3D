#version 330
layout (location = 0) in vec3 aPos;
layout (location = 1) in mat4 aModel;
layout (location = 5) in vec3 aColor;

out vec3 color;

uniform mat4 pv; // projection * view

void main() {
    color = aColor;
    gl_Position = pv * aModel * vec4(aPos, 1.0f);
}
