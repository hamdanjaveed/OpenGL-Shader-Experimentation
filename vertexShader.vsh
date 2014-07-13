#version 400

in vec2 position;
in vec2 textureCoord;

uniform int width;
uniform int height;

out vec2 TextureCoord;
out vec2 TextureSize;

void main() {
	TextureCoord = textureCoord;
	TextureSize = vec2(width, height);
    gl_Position = vec4(position, 0.0, 1.0);
}
