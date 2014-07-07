#version 400

in vec3 Color;
in vec2 TextureCoord;

out vec4 outColor;

uniform sampler2D tex;

void main() {
    outColor = texture(tex, TextureCoord) * vec4(Color, 1.0);
}
