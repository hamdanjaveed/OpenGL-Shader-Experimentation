#version 400

in vec2 position;
in vec3 color;
in vec2 textureCoord;

out vec3 Color;
out vec2 TextureCoord;

void main() {
	TextureCoord = textureCoord;
	Color = color;
    gl_Position = vec4(position, 0.0, 1.0);
}
