#version 330 core

in vec3 color;
in vec2 textureCoords;
out vec4 fragColor;

uniform sampler2D ourTexture;

void main() {
  fragColor = texture(ourTexture, textureCoords);
}
