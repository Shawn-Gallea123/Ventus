#version 330 core

uniform mat4 M;
uniform mat4 V;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTextCoord;

out vec3 myColor;
out vec2 textCoord;

void main() {
	gl_Position = V * M * vec4(aPos.x, aPos.y, aPos.z, 1.0);
	textCoord = aTextCoord;
}