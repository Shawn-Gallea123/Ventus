#version 330 core

out vec4 FragColor;

in vec2 textCoord;

uniform sampler2D myTexture;

void main() {
	vec4 textureColor = texture(myTexture, textCoord);

	if (textureColor.a < 0.1)
		discard;

	FragColor = textureColor;
}