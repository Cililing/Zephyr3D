#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

struct Material {
    sampler2D diffuse;
};

uniform Material material;

void main() {
    vec4 tex_diffuse = texture(material.diffuse, TexCoords);

    if (tex_diffuse.a < 0.1f) {
        discard;
    }

    FragColor = vec4(tex_diffuse.xyz, 1.0f);
}
