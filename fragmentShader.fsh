#version 400

in vec2 TextureCoord;
in vec2 TextureSize;

out vec4 outColor;

uniform sampler2D tex;

void main() {
	float dx = 10.0 * (1.0 / TextureSize.x);
	float dy = 10.0 * (1.0 / TextureSize.y);
	vec2 coord = vec2(dx * floor(TextureCoord.x / dx), dy * floor(TextureCoord.y / dy));
	outColor = texture(tex, coord);
}
